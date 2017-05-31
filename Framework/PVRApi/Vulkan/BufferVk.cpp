/*!
\brief OpenGL ES Implementation of the Buffer class. See BufferVulkan.h.
\file PVRApi/Vulkan/BufferVk.cpp
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/
#include "PVRApi/Vulkan/BufferVk.h"
#include <PVRApi/ApiIncludes.h>
#include "PVRApi/ApiObjects/Texture.h"
#include "PVRNativeApi/Vulkan/VkErrors.h"
#include "PVRNativeApi/Vulkan/NativeObjectsVk.h"
#include "PVRNativeApi/Vulkan/ConvertToVkTypes.h"
#include "PVRApi/Vulkan/ContextVk.h"
#include "PVRNativeApi/Vulkan/BufferUtilsVk.h"
namespace pvr {
namespace api {
<<<<<<< HEAD
namespace impl {
//Future consideration: If it becomes allowed to make this a run-time choice (As opposed to a link-time choice),
//this will need to be re-virtualized and pass through an interface.

void* Buffer_::map(types::MapBufferFlags flags, uint32 offset, uint32 length)
{
	//Safe downcast. We already KNOW that this is our class.
	return static_cast<vulkan::BufferVk_*>(this)->map(flags, offset, length == -1 ? m_size : length);
}

void Buffer_::unmap()
{
	//Safe downcast. We already KNOW that this is our actual type.
	static_cast<vulkan::BufferVk_*>(this)->unmap();
}

bool Buffer_::allocate(uint32 size, types::BufferBindingUse bufferUsage, bool isMappable)
{
	//Safe downcast. We already KNOW that this is our actual type.
	return native_cast(this)->allocate(size, types::BufferBindingUse(bufferUsage), isMappable);
}

bool Buffer_::isMappable()const { return static_cast<const vulkan::BufferVk_*>(this)->isMappable(); }
bool Buffer_::isMapped()const { return static_cast<const vulkan::BufferVk_*>(this)->isMapped(); }

const native::HBuffer_& Buffer_::getNativeObject()const { return native_cast(*this); }

native::HBuffer_& Buffer_::getNativeObject() {	return native_cast(*this); }
}// namespace impl
=======
>>>>>>> 1776432f... 4.3

// AT THIS POINT, IT IS ASSUMED THAT OUR Buffer_ is, in fact, a BufferVulkanImpl. In this sense, to avoid
// virtual function calls, we are de-virtualising Buffer_ into BufferVulkan. So, for each call, our "this"
// pointer (declared type Buffer_*), gets cast into a BufferVulkanImpl* and the calls are done direct (in fact,
// inline) through this pointer.
namespace vulkan {
<<<<<<< HEAD
BufferVk_::BufferVk_(GraphicsContext& context) : Buffer_(context), m_mappedRange(0), m_mappedOffset(0)
=======

BufferVk_::BufferVk_(const GraphicsContext& context) : Buffer_(context)
>>>>>>> 1776432f... 4.3
{
	buffer = VK_NULL_HANDLE; memory = VK_NULL_HANDLE;
}

void BufferVk_::destroy()
{
	if (_context.isValid())
	{
<<<<<<< HEAD
		VkDevice deviceVk =  native_cast(*m_context).getDevice();
=======
		VkDevice deviceVk =  native_cast(*_context).getDevice();
>>>>>>> 1776432f... 4.3
		if (buffer != VK_NULL_HANDLE)
		{
			vk::DestroyBuffer(deviceVk, buffer, NULL);
		}
		else
		{
			Log(Log.Warning, "Buffer Double deletion?");
		}
		if (memory != VK_NULL_HANDLE)
		{
			vk::FreeMemory(deviceVk, memory, NULL);
		}
		else
		{
			Log(Log.Warning, "Buffer Double deletion?");
		}
		memory = VK_NULL_HANDLE;
		buffer = VK_NULL_HANDLE;
		_context.reset();
	}
}

BufferVk_::~BufferVk_()
{
	if (_context.isValid())
	{
		destroy();
	}
	else
	{
		Log(Log.Warning, "Buffer object was not released before context destruction");
	}
}

<<<<<<< HEAD
void* BufferVk_::map(types::MapBufferFlags flags, uint32 offset, uint32 length)
{
	void* mapped;
	if (m_mappedRange)
=======
void* BufferVk_::map_(types::MapBufferFlags flags, uint32 offset, uint32 length)
{
	if (_mappedRange)
>>>>>>> 1776432f... 4.3
	{
		assertion(false, "BufferVk_::map trying to map memory twice");
		return NULL;
	}
	debug_assertion(length + offset <= _size, "BufferVk_::map Trying to map a buffer range greater than its size");
	void* mapped;

	platform::ContextVk& contextVk = native_cast(*_context);

	VkResult rslt = vk::MapMemory(contextVk.getDevice(), memory, offset, length, 0, &mapped);
	if (rslt != VK_SUCCESS)
	{
		Log("BufferVk_::map Failed to to map buffer");
		return NULL;
	}
	_mappedRange = length;
	_mappedOffset = offset;
	_mappedFlags = flags;
	return mapped;
}

void BufferVk_::unmap_()
{
	if (!_mappedRange)
	{
		assertion(false, "Buffer_::unmap trying to un-map un-mapped memory");
		return;
	}
	_mappedRange = 0;
	_mappedOffset = 0;
	_mappedFlags = types::MapBufferFlags(0);

	platform::ContextVk& contextVk = native_cast(*_context);
	VkMappedMemoryRange range = {};
	range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
	range.memory = memory;
<<<<<<< HEAD
	range.offset = m_mappedOffset;
	range.size = m_mappedRange;
	if ((m_mappedFlags & types::MapBufferFlags::Write) != types::MapBufferFlags(0))
	{
		vk::FlushMappedMemoryRanges(contextVk.getDevice(), 1, &range);
	}
	if ((m_mappedFlags & types::MapBufferFlags::Read) != types::MapBufferFlags(0))
=======
	range.offset = _mappedOffset;
	range.size = _mappedRange;
	if ((_mappedFlags & types::MapBufferFlags::Write) != types::MapBufferFlags(0))
	{
		vk::FlushMappedMemoryRanges(contextVk.getDevice(), 1, &range);
	}
	if ((_mappedFlags & types::MapBufferFlags::Read) != types::MapBufferFlags(0))
>>>>>>> 1776432f... 4.3
	{
		vk::InvalidateMappedMemoryRanges(contextVk.getDevice(), 1, &range);
	}
	vk::UnmapMemory(contextVk.getDevice(), memory);
<<<<<<< HEAD
	m_mappedRange = 0;
	m_mappedOffset = 0;
	m_mappedFlags = types::MapBufferFlags(0);
}

bool BufferVk_::allocate(uint32 size, types::BufferBindingUse usage, bool isMappable)
=======
}

bool BufferVk_::allocate_(uint32 size, types::BufferBindingUse usage, bool isMappable)
>>>>>>> 1776432f... 4.3
{
	if(size == 0)
	{
		assertion(size != 0, "Failed to allocate buffer. Allocation size should not be 0");
		return false;
	}
	platform::ContextVk& contextVk = native_cast(*_context);
	if (isAllocated())// re-allocate if neccessary
	{
		Log(Log.Debug, "BufferVulkanImpl::allocate: Vulkan buffer %d was already allocated, deleting it. "
		    "This should normally NOT happen - allocate is private.", buffer);
		destroy();
	}
<<<<<<< HEAD
	m_size = size;
	m_usage = usage;
	m_isMappable = isMappable;
	if (!pvr::utils::vulkan::createBufferAndMemory(contextVk.getDevice(),
	    contextVk.getPlatformContext().getNativePlatformHandles().deviceMemProperties,
	    (isMappable ? VK_MEMORY_PROPERTY_HOST_COHERENT_BIT : VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
	    usage, size, getNativeObject(), NULL))
	{
		return false;
	}
	return true;
=======
	_size = size;
	_usage = usage;
	_isMappable = isMappable;
	return pvr::utils::vulkan::createBufferAndMemory(contextVk.getDevice(),
	    contextVk.getPlatformContext().getNativePlatformHandles().deviceMemProperties,
	    (isMappable ? VK_MEMORY_PROPERTY_HOST_COHERENT_BIT : VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
	    usage, size, *this, NULL);
>>>>>>> 1776432f... 4.3
}

BufferViewVk_::BufferViewVk_(const Buffer& buffer, uint32 offset, uint32 range) :
	impl::BufferView_(buffer, offset, range) {}

}// namespace vulkan
}
}
