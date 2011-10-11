#ifndef OPENSHOT_FRAME_H
#define OPENSHOT_FRAME_H

/**
 * \file
 * \brief Header file for Frame class
 * \author Copyright (c) 2011 Jonathan Thomas
 */

/// Do not include the juce unittest headers, because it collides with unittest++
#define __JUCE_UNITTEST_JUCEHEADER__

#include <iomanip>
#include <sstream>
#include <queue>
#include "Magick++.h"
#include "juce.h"
#include "AudioBufferSource.h"

using namespace std;

namespace openshot
{
	/**
	 * \brief This class represents a single frame of video (i.e. image & audio data)
	 *
	 * FileReaders (such as FFmpegReader) use instances of this class to store the individual frames of video,
	 * which include both the image data (i.e. pixels) and audio samples.
	 */
	class Frame
	{
	private:
		Magick::Image *image;
		juce::AudioSampleBuffer *audio;

	public:
		int number;		///< This is the frame number (starting at 1)
		int pts;		///< This is the presentation timestamp (in frames)

		/// Constructor - blank frame (300x200 blank image, 48kHz audio silence)
		Frame();

		/// Constructor - image only (48kHz audio silence)
		Frame(int number, int width, int height, string color);

		/// Constructor - image only from pixel array (48kHz audio silence)
		Frame(int number, int pts, int width, int height, const string map, const Magick::StorageType type, const void *pixels_);

		/// Constructor - audio only (300x200 blank image)
		Frame(int number, int samples, int channels);

		/// Constructor - image & audio
		Frame(int number, int width, int height, string color, int samples, int channels);

		/// Destructor
		~Frame();

		/// Copy constructor
		Frame ( const Frame &other );

		/// Assignment operator
		Frame& operator= (const Frame& other);

		/// Copy data and pointers from another Frame instance
		void DeepCopy(const Frame& other);

		/// Deallocate image and audio memory
		void DeletePointers();

		/// Display the frame image to the screen (primarily used for debugging reasons)
		void Display();

		/// Get pixel data (as packets)
		const Magick::PixelPacket* GetPixels();

		/// Get pixel data (for only a single scan-line)
		const Magick::PixelPacket* GetPixels(int row);

		/// Get pixel data (for a resized image)
		const Magick::PixelPacket* GetPixels(unsigned int width, unsigned int height, int frame);

		/// Get height of image
		int GetHeight();

		/// Get height of image
		int GetWidth();

		/// Save the frame image
		void Save();

		/// Add audio samples to a specific channel
		void AddAudio(int destChannel, int destStartSample, const float* source, int numSamples, float gainToApplyToSource);

		/// Play audio samples for this frame
		void Play();

	};

}

#endif
