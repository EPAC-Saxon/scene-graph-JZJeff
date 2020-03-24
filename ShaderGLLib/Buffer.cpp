#include "Buffer.h"
#include <exception>
#include <stdexcept>

namespace sgl {


	Buffer::Buffer(
		const BufferType buffer_type /*= BufferType::ARRAY_BUFFER*/,
		const BufferUsage buffer_usage /*= BufferUsage::STATIC_DRAW*/) :
		buffer_type_(buffer_type),
		buffer_usage_(buffer_usage)

	{
#pragma message ("You have to complete this code!")

		glGenBuffers(1, &buffer_object_);
	}
	
	Buffer::~Buffer()
	{
#pragma message ("You have to complete this code!")	
		glDeleteBuffers(1, &buffer_object_);
	}

	void Buffer::Bind() const
	{
#pragma message ("You have to complete this code!")
		glBindBuffer(static_cast<GLenum>(buffer_type_), buffer_object_ );
	}

	void Buffer::UnBind() const
	{
#pragma message ("You have to complete this code!")	
		glBindBuffer(static_cast<GLenum>(buffer_type_), 0);
	}

	void Buffer::BindCopy(
		const size_t size, 
		const void* data /*= nullptr*/) const
	{
#pragma message ("You have to complete this code!")	

		Bind();

		glBufferData(
			static_cast<GLenum>(buffer_type_),
			size,
			&data,
			GL_STATIC_DRAW);

		UnBind();
	}

} // End namespace sgl.
