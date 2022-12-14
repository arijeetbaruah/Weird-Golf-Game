#pragma once
#ifdef _ORBIS
#include "../../Common/ShaderBase.h"
#include "PS4MemoryAware.h"

#include <gnm.h>
#include <gnmx\shaderbinary.h>
#include <gnmx\context.h>

#include <shader\binary.h>

using namespace sce;

namespace NCL {
	namespace PS4 {
		class PS4Shader : public Rendering::ShaderBase, public PS4MemoryAware
		{
			friend class PS4RendererBase;
		public:
			~PS4Shader();

			static PS4Shader* GenerateShader(const string& vertex, const string& pixel);

			int		GetConstantBuffer(const string &name);			
			void	SubmitShaderSwitch(Gnmx::GnmxGfxContext& cmdList);

			static bool LoadShaderBinary(const string &name, char*& into, int& dataSize);

		protected:
			PS4Shader();

			void ReloadShader() override {
				//we load binaries in directly...
			}

			void GenerateVertexShader(const string&name, bool makeFetch);

			void GeneratePixelShader(const string&name);

			void GenerateFetchShader(char* binData);

			bool LoadShaderText(const string &name, string&into);



			bool ShaderIsBinary(const string& name);

		protected:
			void*							fetchShader;

			sce::Shader::Binary::Program	vertexBinary;
			Gnmx::VsShader*					vertexShader;
			Gnmx::InputOffsetsCache			vertexCache;

			sce::Shader::Binary::Program	pixelBinary;
			Gnmx::PsShader*					pixelShader;
			Gnmx::InputOffsetsCache			pixelCache;
		};
	}
}
#endif
