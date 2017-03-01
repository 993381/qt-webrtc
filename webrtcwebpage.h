#ifndef WEBRTCWEBPAGE_H
#define WEBRTCWEBPAGE_H

#include <QWebEnginePage>
class WebRTCWebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit WebRTCWebPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

protected:
    bool certificateError(const QWebEngineCertificateError &error) override;
};

#endif // WEBRTCWEBPAGE_H
