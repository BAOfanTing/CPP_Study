#ifndef QFACEOBJECT_H
#define QFACEOBJECT_H

#include <QObject>
#include <seeta/FaceDatabase.h>
#include <seeta/FaceEngine.h>
#include <opencv.hpp>
using namespace cv;
using namespace seeta;

//人脸数据存储，人脸检测，人脸识别
class QFaceObject : public QObject
{
    Q_OBJECT
public:

    explicit QFaceObject(QObject *parent = nullptr);

    ~QFaceObject();

public slots:
    // 人脸注册函数，用于将人脸图像注册到人脸数据库中
    // 参数：faceImage - OpenCV Mat 对象，代表人脸图像
    // 返回值：int64_t，注册成功返回人脸 ID，失败返回 -1
    int64_t face_register(cv::Mat &faceImage);

    // 人脸识别函数，用于识别给定图像中的人脸
    // 参数：faceImage - OpenCV Mat 对象，代表人脸图像
    // 返回值：int，识别成功返回人脸 ID，失败返回 -1
    int face_query(cv::Mat &faceImage);

signals:

private:
    // seeta 人脸引擎指针
    seeta::FaceEngine *fengineptr;
};

#endif // QFACEOBJECT_H
