/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#include "ImageFormatTIF.h"

bool ImageFormatTIF::ClassInitialized = false;

//String ImageFormatTIF::DefaultResources[] = {
//    NUL(char*)
//};


ImageFormatTIF::ImageFormatTIF (ImageFormatDialog* dialog) : 
    PixelImageFormat("TIFFformat", dialog)
{

}

ImageFormatTIF::~ImageFormatTIF()
{
}


void ImageFormatTIF::initialize()
{
    if (!ImageFormatTIF::ClassInitialized) {
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    PixelImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormatTIF::DefaultResources);
	ImageFormatTIF::ClassInitialized = true;
    }
}

bool ImageFormatTIF::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatTIF);
    if (s == classname)
	return true;
    else
	return this->ImageFormat::isA(classname);
}

