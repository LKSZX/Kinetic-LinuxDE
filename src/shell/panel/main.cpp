#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QTimer>

class KineticPanel : public QWidget {
public:
    KineticPanel() {
        // 设置背景颜色，方便在黑漆漆的窗口里一眼看到它
        setStyleSheet("background-color: #2c3e50; color: white; border-bottom: 2px solid #3498db;");
        
        auto *layout = new QVBoxLayout(this);
        auto *label = new QLabel("Kinetic Project | Welcome, Zane Lukas", this);
        label->setAlignment(Qt::AlignCenter);
        
        auto *timeLabel = new QLabel(this);
        layout->addWidget(label);
        layout->addWidget(timeLabel);

        // 简单的时钟刷新逻辑
        auto *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [timeLabel]() {
            timeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        });
        timer->start(1000);

        // 初始大小（后续我们会通过协议把它固定在顶部）
        resize(800, 60);
    }
};

int main(int argc, char *argv[]) {
    // 强制使用 Wayland 插件
    qputenv("QT_QPA_PLATFORM", "wayland");
    
    QApplication a(argc, argv);
    KineticPanel w;
    w.show();
    return a.exec();
}
