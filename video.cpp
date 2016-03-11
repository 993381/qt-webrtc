#include "video.h"


#include <QtWidgets>
//#include <QtWebEngineWidgets>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
//#include <QWebEnginePage>

#include "mainwindow.h"

template<typename Arg, typename R, typename C>
struct InvokeWrapper {
    R *receiver;
    void (C::*memberFun)(Arg);
    void operator()(Arg result) {
        (receiver->*memberFun)(result);
    }
};

template<typename Arg, typename R, typename C>
InvokeWrapper<Arg, R, C> invoke(R *receiver, void (C::*memberFun)(Arg))
{
    InvokeWrapper<Arg, R, C> wrapper = {receiver, memberFun};
    return wrapper;
}

//! [1]

Video::Video(const QUrl& url)
{
    progress = 0;

    QFile file;
    file.setFileName(":/jquery.min.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    file.close();
//! [1]

//! [2]
    view = new QWebEngineView(this);
    view->load(url);
    connect(view->page(), SIGNAL(featurePermissionRequested(QUrl,QWebEnginePage::Feature)),SLOT(test(QUrl,QWebEnginePage::Feature)));

//    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
//    connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
//    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
//    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

//    locationEdit = new QLineEdit(this);
//    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
//    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

//    QToolBar *toolBar = addToolBar(tr("Navigation"));
//    toolBar->addAction(view->pageAction(QWebEnginePage::Back));
//    toolBar->addAction(view->pageAction(QWebEnginePage::Forward));
//    toolBar->addAction(view->pageAction(QWebEnginePage::Reload));
//    toolBar->addAction(view->pageAction(QWebEnginePage::Stop));
//    toolBar->addWidget(locationEdit);
////! [2]

//    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
//    QAction* viewSourceAction = new QAction("Page Source", this);
//    connect(viewSourceAction, SIGNAL(triggered()), SLOT(viewSource()));
//    viewMenu->addAction(viewSourceAction);

////! [3]
//    QMenu *effectMenu = menuBar()->addMenu(tr("&Effect"));
//    effectMenu->addAction("Highlight all links", this, SLOT(highlightAllLinks()));

//    rotateAction = new QAction(this);
//    rotateAction->setIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
//    rotateAction->setCheckable(true);
//    rotateAction->setText(tr("Turn images upside down"));
//    connect(rotateAction, SIGNAL(toggled(bool)), this, SLOT(rotateImages(bool)));
//    effectMenu->addAction(rotateAction);

//    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
//    toolsMenu->addAction(tr("Remove GIF images"), this, SLOT(removeGifImages()));
//    toolsMenu->addAction(tr("Remove all inline frames"), this, SLOT(removeInlineFrames()));
//    toolsMenu->addAction(tr("Remove all object elements"), this, SLOT(removeObjectElements()));
//    toolsMenu->addAction(tr("Remove all embedded elements"), this, SLOT(removeEmbeddedElements()));

    setCentralWidget(view);
}
//! [3]
void Video::test(QUrl q, QWebEnginePage::Feature f) {
    view->page()->setFeaturePermission(q, f,
    QWebEnginePage::PermissionGrantedByUser);
}
void Video::viewSource()
{
    QTextEdit* textEdit = new QTextEdit(NULL);
    textEdit->setAttribute(Qt::WA_DeleteOnClose);
    textEdit->adjustSize();
    textEdit->move(this->geometry().center() - textEdit->rect().center());
    textEdit->show();

    view->page()->toHtml(invoke(textEdit, &QTextEdit::setPlainText));
}

//! [4]
void Video::adjustLocation()
{
    locationEdit->setText(view->url().toString());
}

void Video::changeLocation()
{
    QUrl url = QUrl::fromUserInput(locationEdit->text());
    view->load(url);
    view->setFocus();
}
//! [4]

//! [5]
void Video::adjustTitle()
{
    if (progress <= 0 || progress >= 100)
        setWindowTitle(view->title());
    else
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
}

void Video::setProgress(int p)
{
    progress = p;
    adjustTitle();
}
//! [5]

//! [6]
void Video::finishLoading(bool)
{
    progress = 100;
    adjustTitle();
    view->page()->runJavaScript(jQuery);

    rotateImages(rotateAction->isChecked());
}
//! [6]

//! [7]
void Video::highlightAllLinks()
{
    // We append '; undefined' after the jQuery call here to prevent a possible recursion loop and crash caused by
    // the way the elements returned by the each iterator elements reference each other, which causes problems upon
    // converting them to QVariants.
    QString code = "qt.jQuery('a').each( function () { qt.jQuery(this).css('background-color', 'yellow') } ); undefined";
    view->page()->runJavaScript(code);
}
//! [7]

//! [8]
void Video::rotateImages(bool invert)
{
    QString code;

    // We append '; undefined' after each of the jQuery calls here to prevent a possible recursion loop and crash caused by
    // the way the elements returned by the each iterator elements reference each other, which causes problems upon
    // converting them to QVariants.
    if (invert)
        code = "qt.jQuery('img').each( function () { qt.jQuery(this).css('-webkit-transition', '-webkit-transform 2s'); qt.jQuery(this).css('-webkit-transform', 'rotate(180deg)') } ); undefined";
    else
        code = "qt.jQuery('img').each( function () { qt.jQuery(this).css('-webkit-transition', '-webkit-transform 2s'); qt.jQuery(this).css('-webkit-transform', 'rotate(0deg)') } ); undefined";
    view->page()->runJavaScript(code);
}
//! [8]

//! [9]
void Video::removeGifImages()
{
    QString code = "qt.jQuery('[src*=gif]').remove()";
    view->page()->runJavaScript(code);
}

void Video::removeInlineFrames()
{
    QString code = "qt.jQuery('iframe').remove()";
    view->page()->runJavaScript(code);
}

void Video::removeObjectElements()
{
    QString code = "qt.jQuery('object').remove()";
    view->page()->runJavaScript(code);
}

void Video::removeEmbeddedElements()
{
    QString code = "qt.jQuery('embed').remove()";
    view->page()->runJavaScript(code);
}
//! [9]



//Video::Video(QWidget *parent) : QMainWindow(parent)
//{

//}

