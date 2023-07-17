#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QThread>
#include "lyrics.h"
namespace Ui {
class MusicPlayer;
}

class MusicPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayer(QWidget *parent = 0);
    ~MusicPlayer();

private slots:
    void addSongs();
    void playPause();
    void playNext();
    void playPrevious();
    void posChanged(qint64 pos);
    void durChanged(qint64 dur);
    void setPos(int pos);
    void clearList();
    void delectSong();
    void volumeSilence();
    void setVol(int vol);
    void hideShow();
    void redVolume();
    void addVolume();
    void setPlayTime();
    void on_back_ptn_clicked();

private:
    Ui::MusicPlayer *ui;
private:
    QMediaPlayer* player;
    QMediaPlaylist* playList;
    QAction* action_hideShow;
    QAction* action_addSongs;
    QAction* action_playPause;
    QAction* action_stop;
    QAction* action_previous;
    QAction* action_next;
    QAction* action_addVolume;
    QAction* action_redVolume;
    QAction* action_quit;
    Lyrics lyrics;
    int lyricsID = 0;
    QString playPath;
     QString presentTime;
     QString totalTime;
protected:
    void contextMenuEvent(QContextMenuEvent* );
};
#endif // WIDGET_H
