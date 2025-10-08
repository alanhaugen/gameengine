#include <QWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QObject>


class displayWidget : public QWidget {
    //Q_OBJECT

public:
    displayWidget(QWidget *parent = nullptr) : QWidget(parent) {
        stackedWidget = new QStackedWidget(this);

        imageLabel = new QLabel("Image Preview");
        imageLabel->setAlignment(Qt::AlignCenter);

        // QMediaPlayer* audioPlayer = new QMediaPlayer(this);
        // audioWidget = new QWidget;
        // QVBoxLayout *audioLayout = new QVBoxLayout(audioWidget);
        // audioLayout->addWidget(new QLabel("Playing .ogg file..."));

        objViewer = new QLabel("3D .obj Viewer Placeholder");
        objViewer->setAlignment(Qt::AlignCenter);

        stackedWidget->addWidget(imageLabel);   // index 0
        //stackedWidget->addWidget(audioWidget);  // index 1
        stackedWidget->addWidget(objViewer);    // index 2

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(stackedWidget);
        setLayout(mainLayout);
    }
public slots:
    void previewFile(const QString &path) {
        QFileInfo fileInfo(path);
        QString ext = fileInfo.suffix().toLower();

        if (ext == "png" || ext == "jpg") {
            QPixmap pix(path);
            imageLabel->setPixmap(pix.scaled(400, 400, Qt::KeepAspectRatio));
            stackedWidget->setCurrentWidget(imageLabel);
        } /*else if (ext == "ogg") {
            audioPlayer->setMedia(QUrl::fromLocalFile(path));
            audioPlayer->play();
            stackedWidget->setCurrentWidget(audioWidget);
        }*/ else if (ext == "obj") {
            objViewer->setText("Loaded .obj file: " + fileInfo.fileName());
            stackedWidget->setCurrentWidget(objViewer);
        } else {
            imageLabel->setText("Unsupported file type");
            stackedWidget->setCurrentWidget(imageLabel);
        }
    }

private:
    QStackedWidget *stackedWidget;
    QLabel *imageLabel;
    QLabel *objViewer;
    QWidget *audioWidget;
    //QMediaPlayer *audioPlayer;
};
