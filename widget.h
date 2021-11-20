#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QRandomGenerator64>
#include <QDir>
#include <QDebug>
#include <QPainter>
#include <QJsonObject>
#include <QJsonDocument>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QList <QLineEdit*> SourcePathsLineEdits;
    QLineEdit *Enter_NFT_Size;
    QList <QLabel*>    SourcePathDeclerationLabel;
    QList <QStringList> SourcePaths;
    QList <QList<QPixmap>> Layers_Images;
    QList <QList<QPixmap>> Sources_Images;
    QList <QPixmap> Current_Images;
    QPushButton *GetAllPathsButton;
    QPushButton *StartButton,*ReadButton,*MixButton;
    QLineEdit *ResultsPathLineEdit,*ResultPath;
    QList <QStringList> ImageNames;
    QList <QStringList> LayerImagesNames;
    QList <int> ResultNamesIsChanged;
    QStringList ExistingImages;
    QLabel *input_info;
    int result_counter=0;
    int ResultCount=0;
    int max_res=1;
    int layer_count=0;

private slots:
    void Create_LineEdits(int count);

    void on_enter_btn_released();

    void clicked_GetAllPath();

    QStringList Read_Images_Name(QString Directory_Path);

    int Generate_Random_Number(int begin_point,int end_point);

    bool Check_Image_Exist();

    void paste_all_layer();

    QPixmap Paste_Image_to_Another_Image(QString background_image_url, QString source_image_url);

    void Save_Image(QString image_path,QPixmap result_image);

    void NFT_Results_Producer();

    QPixmap Convert_QPixmap(QString Source_Path);

    QPixmap Paste_Image_to_Another_Image_withouturl(QPixmap background_image, QPixmap source_image);

    void write_data_json_file();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
