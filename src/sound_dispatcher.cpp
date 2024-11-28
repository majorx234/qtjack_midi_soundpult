#include <sound_dispatcher.h>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>

using namespace Phonon;
Sound_Dispatcher::Sound_Dispatcher(QWidget *parent) : QObject(parent) {
    audio_output = new Phonon::AudioOutput(Phonon::MusicCategory, parent);
}

int Sound_Dispatcher::add_instrument(std::string name, QString path_to_wave) {
    Phonon::MediaSource source(QUrl::fromLocalFile(path_to_wave));
    MediaObject* obj = new MediaObject;
    obj->setCurrentSource( source);
    instruments_media_obj[name] = obj;

    Phonon::createPath(instruments_media_obj[name], audio_output);
    return 0;
}

int Sound_Dispatcher::play_instrument(std::string name) {
    instruments_media_obj[name]->play();
    return 0;
}
