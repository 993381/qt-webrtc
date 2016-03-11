#ifndef VIDEO_H
#define VIDEO_H

#include <QMainWindow>

#include <QtWidgets>
#include <QWebEnginePage>

QT_BEGIN_NAMESPACE
class QWebEngineView;
class QWebEnginePage;
class QLineEdit;
QT_END_NAMESPACE

//! [1]
class Video : public QMainWindow
{
    Q_OBJECT

public:
    Video(const QUrl& url);

protected slots:

    void adjustLocation();
    void changeLocation();
    void adjustTitle();
    void setProgress(int p);
    void finishLoading(bool);

    void viewSource();

    void highlightAllLinks();
    void rotateImages(bool invert);
    void removeGifImages();
    void removeInlineFrames();
    void removeObjectElements();
    void removeEmbeddedElements();

    void test(QUrl q, QWebEnginePage::Feature f);
private:
    QString jQuery;
    QWebEngineView *view;
    QLineEdit *locationEdit;
    QAction *rotateAction;
    int progress;
//! [1]
};

#endif // VIDEO_H
