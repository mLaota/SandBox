"""
This script requires PyAL, the Python wrapper for OpenAL and Python >= 3.6.

The Haas Effect:
    The Haas Effect [often referred to as the precedence effect] is a
    psychoacoustical phenomenon that describes the perceived location of
    two binaural sounds when separated by a small delay. Applying delays
    below the human echo threshold will result in the two sounds being
    perceived as a singular audio event with a perceived spatial location
    dominated by the effect of the first sound heard.

    This is effect can be leveraged to spatialize a mono audio source as
    demonstrated in the "haas" function below.

References:
    The Precedence Effect in Sound Localization
        (https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4310855/)

"""

from openal import al, alc
import os
import sys
import time
import wave


def get_sources():
    """
    Instantiates and returns a left, center and right audio source.

    Returns:
        A tuple of (LEFT, RIGHT, CENTER) localized sources.
    """
    POS_LEFT, POS_CENTER, POS_RIGHT = [(i, 0, 0) for i in range(-1, 2)]

    # Instantiate the sources
    sources = left, right, center = tuple(al.ALuint(i) for i in range(0, 3))
    for src in sources:
        al.alGenSources(1, src)
        al.alSourcef(src, al.AL_PITCH, 1)  # plays at default pitch.
        al.alSourcef(src, al.AL_GAIN, 1)
        al.alSource3f(src, al.AL_VELOCITY, 0, 0, 0)
        al.alSourcei(src, al.AL_LOOPING, al.AL_FALSE)

    # Assign a position to each source.
    al.alSource3f(left, al.AL_POSITION, *POS_LEFT)
    al.alSource3f(right, al.AL_POSITION, *POS_RIGHT)
    al.alSource3f(center, al.AL_POSITION, *POS_CENTER)

    return left, right, center


def haas(path_to_wav):
    """
    Demonstrates the Haas Effect using the given <=16-bit WAV file.
    Plays the given audio three times, perceived from the center,
    left and right, respectively.
    """
    # Load the WAVE file.
    path_to_wav = sys.argv[1]
    wav = wave.open(path_to_wav)

    # Save some properties of the wav file.
    wav_name = path_to_wav.rsplit(os.path.sep).pop()
    channels = wav.getnchannels()
    bitrate = wav.getsampwidth() * 8
    samplerate = wav.getframerate()
    wav_buffer = wav.readframes(wav.getnframes())
    wav_fmt_map = {
        (1, 8): al.AL_FORMAT_MONO8,
        (2, 8): al.AL_FORMAT_STEREO8,
        (1, 16): al.AL_FORMAT_MONO16,
        (2, 16): al.AL_FORMAT_STEREO16,
        # 24-bit ints and floats are not supported by OpenAL out of the box.
    }
    alformat = wav_fmt_map[(channels, bitrate)]

    # Get the playback device / context.
    device = alc.alcOpenDevice(None)  # opens the default device.
    context = alc.alcCreateContext(device, None)  # no attributes needed.
    alc.alcMakeContextCurrent(context)

    # Prepare the playback buffer.
    buffer = al.ALuint(0)
    al.alGenBuffers(1, buffer)
    al.alBufferData(buffer, alformat, wav_buffer, len(wav_buffer), samplerate)

    # Initialize and configure the sources for playback.
    sources = src_left, src_right, src_center = get_sources()
    for src in sources:
        al.alSourceQueueBuffers(src, 1, buffer)

    def play(delay_ms=15, dominant='left'):
        """
        Plays the above wav file from a perceived location.

        Args:
            delay_ms: The delay between the first and second source.
            dominant: The dominant location to play the audio from.
        """
        dominant = dominant.lower()
        directions = {'left', 'right', 'center'}
        GAIN = 1.

        if dominant not in directions or dominant == 'center':
            al.alSourcePlay(src_center)
        else:
            # Determine the order in which to play the sources.
            play_order = [src_left, src_right]  # left-dominant.
            if dominant == 'right':
                play_order.reverse()

            # Adjust the gains for a more biased stereo effect.
            al.alSourcef(play_order[0], al.AL_GAIN, GAIN * 0.5)
            al.alSourcef(play_order[1], al.AL_GAIN, GAIN * 0.4)

            # Apply the precedence effect by playing the sources
            # 'delay_ms' milliseconds apart.
            al.alSourcePlay(play_order[0])
            time.sleep(delay_ms / 1000)
            al.alSourcePlay(play_order[1])

        # Wait until playback is finished, then delete the buffer.
        duration = wav.getnframes() / samplerate
        time.sleep(duration)

    # Play the wav file localized at each of the given positions.
    for position in ['center', 'left', 'right']:
        print(f'Playing {wav_name} perceived from the {position}.')
        play(dominant=position)
        print('Done playing.\n')

    # Clean up.
    for src in sources:
        al.alDeleteSources(1, src)
    al.alDeleteBuffers(1, buffer)
    alc.alcDestroyContext(context)
    alc.alcCloseDevice(device)

    return 0


if __name__ == '__main__':
    if len(sys.argv) < 2:
        raise ValueError('Please provide the path to the audio '
                         'file you would like to use.')
    elif len(sys.argv) > 2:
        raise ValueError('Only one audio file is accepted by this '
                         'script. Please ensure that if your path '
                         'contains spaces, the path is wrapped in '
                         'quotes.')
    sys.exit(haas(sys.argv[1]))
