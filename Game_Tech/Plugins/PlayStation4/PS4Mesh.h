#pragma once
#ifdef _ORBIS
#include "../../Common/MeshGeometry.h"
#include "PS4MemoryAware.h"

#include <gnm.h>

namespace NCL {
	namespace PS4 {
		using namespace sce;
		class PS4Mesh : public NCL::MeshGeometry, public PS4MemoryAware
		{
			friend class PS4RendererBase;
		public:
			static PS4Mesh* GenerateTriangle();
			static PS4Mesh* GenerateQuad();
			static PS4Mesh* GenerateSinglePoint();

			void UpdateMesh()
			{
				indexType = sce::Gnm::IndexSize::kIndexSize32;
				SetPrimitiveType(NCL::GeometryPrimitive::Triangles);
				UploadToGPU();
			}
			void SetIndexType(sce::Gnm::IndexSize type)
			{
				indexType = type;
			}
			PS4Mesh();
			~PS4Mesh();
			//Gpu simply has a 4 byte alignment!
	protected:
			struct MeshVertex
			{
				float position[3];
				float textureCoord[2];
				float normal[3];
				float tangent[3];
			};

			int* indexBuffer;
			MeshVertex* vertexBuffer;

			void	SubmitDraw(Gnmx::GnmxGfxContext& cmdList, Gnm::ShaderStage stage);

			void	InitAttributeBuffer(sce::Gnm::Buffer &buffer, Gnm::DataFormat format, void*offset);

		protected:	
			PS4Mesh(const std::string&filename);

		protected:
			void UploadToGPU() override;


			sce::Gnm::IndexSize		indexType;



			int vertexDataSize;
			int indexDataSize;

			sce::Gnm::Buffer*	attributeBuffers = nullptr;
			int					attributeCount;
		};
	}
}
#endif
