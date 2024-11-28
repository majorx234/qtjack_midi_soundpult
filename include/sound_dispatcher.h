#ifndef SOUND_DISPATCHER_H
#define SOUND_DISPATCHER_H

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>

#include <QObject>
#include <QWidget>
#include <QString>
//#include <QAudioOutput>
using namespace Phonon;

class Sound_Dispatcher: QObject {
  Q_OBJECT
private:
  AudioOutput* audio_output;
  std::map <std::string, MediaObject*> instruments_media_obj;
public:
  Sound_Dispatcher(QWidget *parent = 0);
  int add_instrument(std::string name,QString path_to_wave);
  int play_instrument(std::string name);
};

#endif
