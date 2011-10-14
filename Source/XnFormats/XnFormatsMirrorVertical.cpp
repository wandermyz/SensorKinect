/*****************************************************************************
*                                                                            *
*  PrimeSense Sensor 5.0 Alpha                                               *
*  Copyright (C) 2010 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of PrimeSense Common.                                   *
*                                                                            *
*  PrimeSense Sensor is free software: you can redistribute it and/or modify *
*  it under the terms of the GNU Lesser General Public License as published  *
*  by the Free Software Foundation, either version 3 of the License, or      *
*  (at your option) any later version.                                       *
*                                                                            *
*  PrimeSense Sensor is distributed in the hope that it will be useful,      *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
*  GNU Lesser General Public License for more details.                       *
*                                                                            *
*  You should have received a copy of the GNU Lesser General Public License  *
*  along with PrimeSense Sensor. If not, see <http://www.gnu.org/licenses/>. *
*                                                                            *
*****************************************************************************/






//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <XnPlatform.h>
#include <XnCore.h>
#include "XnFormats.h"
#include <XnOS.h>
#include <XnLog.h>

//Added by Wander

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define XN_MIRROR_MAX_LINE_SIZE	1920*3

//---------------------------------------------------------------------------
// Code
//---------------------------------------------------------------------------

XN_FORMATS_API XnStatus XnFormatsMirrorVerticalPixelData(XnOutputFormats nOutputFormat, XnUChar* pBuffer, XnUInt32 nBufferSize, XnUInt32 nXRes)
{
	XnUInt32 pixelSizes[XN_OUTPUT_FORMATS_COUNT];
	xnOSMemSet(&pixelSizes, 0, sizeof(pixelSizes));
	pixelSizes[XN_OUTPUT_FORMAT_SHIFT_VALUES] = 2;
	pixelSizes[XN_OUTPUT_FORMAT_DEPTH_VALUES] = 2;
	pixelSizes[XN_OUTPUT_FORMAT_GRAYSCALE8] = 1;
	pixelSizes[XN_OUTPUT_FORMAT_GRAYSCALE16] = 2;
	pixelSizes[XN_OUTPUT_FORMAT_YUV422] = 0;
	pixelSizes[XN_OUTPUT_FORMAT_RGB24] = 3;

	XnUChar lineBuffer[XN_MIRROR_MAX_LINE_SIZE];
	XnUInt32 pixelSize = pixelSizes[nOutputFormat];

	if (pixelSize == NULL)
	{
		xnLogError(XN_MASK_FORMATS, "Mirror vertical was not implemented for output format %d", nOutputFormat);
		return XN_STATUS_ERROR;
	}

	XnUInt lineSize = nXRes * pixelSize;
	XnUChar* higherLine = pBuffer;
	XnUChar* lowerLine = pBuffer + nBufferSize - lineSize;

	while (higherLine < lowerLine)
	{
		xnOSMemCopy(lineBuffer, higherLine, lineSize);
		xnOSMemCopy(higherLine, lowerLine, lineSize);
		xnOSMemCopy(lowerLine, lineBuffer, lineSize);

		higherLine += lineSize;
		lowerLine -= lineSize;
	}

	return (XN_STATUS_OK);
}