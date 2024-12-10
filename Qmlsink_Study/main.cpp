#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include <QRunnable>
#include <gst/gst.h>
#include <QTimer>

class SetPlaying : public QRunnable
{
public:
    SetPlaying(GstElement *);
    ~SetPlaying();

    void run ();

private:
    GstElement * pipeline_;
};

SetPlaying::SetPlaying (GstElement * pipeline)
{
    this->pipeline_ = pipeline ? static_cast<GstElement *> (gst_object_ref (pipeline)) : NULL;
}

SetPlaying::~SetPlaying ()
{
    if (this->pipeline_)
        gst_object_unref (this->pipeline_);
}

void
SetPlaying::run ()
{
    if (this->pipeline_)
        gst_element_set_state (this->pipeline_, GST_STATE_PLAYING);
}

void createPipeline(GstElement **pipeline, GstElement **src, GstElement **glupload, GstElement **sink) {
    *pipeline = gst_pipeline_new(NULL);
    *src = gst_element_factory_make("videotestsrc", NULL);
    *glupload = gst_element_factory_make("glupload", NULL);
    *sink = gst_element_factory_make("qmlglsink", NULL);

    g_assert(*src && *glupload && *sink);
}

int main(int argc, char *argv[])
{
    int ret;

    gst_init (&argc, &argv);

    {
        QGuiApplication app(argc, argv);
        QQmlApplicationEngine engine;
        GstElement *pipeline1,*src1,*glupload1,*sink1;
        GstElement *pipeline2,*src2,*glupload2,*sink2;

        createPipeline(&pipeline1, &src1, &glupload1, &sink1);
        createPipeline(&pipeline2,&src2,&glupload2,&sink2);

        gst_bin_add_many(GST_BIN(pipeline1), src1, glupload1, sink1, nullptr);
        gst_bin_add_many(GST_BIN(pipeline2), src2, glupload2, sink2, nullptr);
        gst_element_link_many(src1, glupload1, sink1, nullptr);
        gst_element_link_many(src2, glupload2, sink2, nullptr);

        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

        QQuickWindow *rootObject = static_cast<QQuickWindow *>(engine.rootObjects().first());
        QQuickItem* videoItem1 = rootObject->findChild<QQuickItem*>("videoItem1");
        QQuickItem* videoItem2 = rootObject->findChild<QQuickItem*>("videoItem2");

        g_object_set(sink1, "widget", videoItem1, nullptr);
        g_object_set(sink2, "widget", videoItem2, nullptr);
        rootObject->scheduleRenderJob(new SetPlaying(pipeline1), QQuickWindow::BeforeSynchronizingStage);
        rootObject->scheduleRenderJob(new SetPlaying(pipeline2), QQuickWindow::BeforeSynchronizingStage);


        ret = app.exec();

        gst_element_set_state(pipeline1, GST_STATE_NULL);
        gst_element_set_state(pipeline2, GST_STATE_NULL);

        gst_object_unref(pipeline1);
        gst_object_unref(pipeline2);
    }

    gst_deinit ();

    return ret;
}
