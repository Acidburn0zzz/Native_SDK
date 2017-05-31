<<<<<<< HEAD
/*!*********************************************************************************************************************
\file         PVRApi\OGLES\PipelineLayoutGles.h
\author       PowerVR by Imagination, Developer Technology Team
\copyright    Copyright (c) Imagination Technologies Limited.
\brief         Definitions of the OpenGL ES implementation of the RenderPass.
***********************************************************************************************************************/
//!\cond NO_DOXYGEN
=======
/*!
\brief Definitions of the OpenGL ES implementation of the RenderPass.
\file PVRApi/OGLES/PipelineLayoutGles.h
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/
>>>>>>> 1776432f... 4.3
#pragma once
#include "PVRApi/ApiObjects/PipelineLayout.h"
#include "PVRNativeApi/OGLES/NativeObjectsGles.h"
namespace pvr {
namespace api {
namespace gles {

class PipelineLayoutGles_ : public impl::PipelineLayout_, public native::HPipelineLayout_
{
public:
	PipelineLayoutGles_(const GraphicsContext& device) : PipelineLayout_(device) {}
	bool init(const PipelineLayoutCreateParam& createParam)
	{
		_desc = createParam;
		return true;
	}
};
typedef RefCountedResource<PipelineLayoutGles_> PipelineLayoutGles;
}
}
}
<<<<<<< HEAD
//!\endcond
=======
>>>>>>> 1776432f... 4.3
