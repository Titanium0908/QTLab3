#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <gamelist.h>
#include <QQmlContext>
#include <QStringList>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    GameList viewModel;

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextObject(&viewModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
