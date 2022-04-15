#include "gamelist.h"
#include "game.h"
#include <QDebug>
#include "QStringList"
#include "QStringListModel"
#include "QString"

GameList::GameList(QObject *parent) : QAbstractListModel(parent)
{
    Game *game1 = new Game("Cs", "valve", 10, "pc");
    Game *game2 = new Game("Dota", "valve", 9, "pc");
    Game *game3 = new Game("lol", "Riot Games", 13, "pc");

    beginInsertRows(QModelIndex(),games.size(),games.size());
    games.append(*game1);
    games.append(*game2);
    games.append(*game3);
    endInsertRows();

    this->platforms = Game::allPlatforms();
}

QAbstractListModel* GameList::getModel()
{
    return this;
}

int GameList::rowCount(const QModelIndex&) const
{
    return games.size();
}

QVariant GameList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= games.size())
        return QVariant();
    switch (role) {
        case name:
            return QVariant(games.at(index.row()).getName());
        case developer:
            return QVariant(games.at(index.row()).getDeveloper());
        case age:
            return QVariant(games.at(index.row()).getAge());
        case platform:
            return QVariant(games.at(index.row()).getPlatform());
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> GameList::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[name] = "GameName";
    roles[developer] = "GameDeveloper";
    roles[age] = "GameAge";
    roles[platform] = "GamePlatform";

    return roles;
}

void GameList::add(const QString Name, const QString Developer, const int Age, const QString Platform)
{
    Game cat;
    cat.setName(Name);
    cat.setAge(Age);
    cat.setDeveloper(Developer);
    cat.setPlatform(Platform);

    beginInsertRows(QModelIndex(),games.size(),games.size());
    games.append(cat);
    endInsertRows();
}
void GameList::edit(const QString Name, const QString Developer, const int Age, const QString Platform, const int index)
{
    if(index >= 0 && index < games.size())
    {
        auto& editable_cat = games[index];
        editable_cat.setName(Name);
        editable_cat.setDeveloper(Developer);
        editable_cat.setAge(Age);
        editable_cat.setPlatform(Platform);

        auto modelIndex = createIndex(index, 0);
        dataChanged(modelIndex, modelIndex);
        qDebug() << games[index].getName();
    }
    else qDebug() << "Выбран неверный индекс";
}
void GameList::remove(const int index)
{
    if (index >= 0 && index < games.size())
    {
        beginRemoveRows(QModelIndex(), index, index);
        games.removeAt(index);
        endRemoveRows();
    }
    else qDebug() << "Неверный индекс удаления";
}
QString GameList::find(QString txt)
{
    int amount = 0;
    for (int i = 0; i < games.length(); i++)
    {
        if(games[i].getPlatform() == txt)
        {
            amount++;
        }
    }
    QString tmp = QString::number(amount);
    return tmp;
}

QStringList GameList::getPlatforms()
{
    return platforms;
}


