#include <Ui/ToolbarTool.h>

#include <GeometryEditor.h>

#include <Geometry/Operations/CreatePrimitiveOperation.h>
#include <Ui/OperationArguments/DropdownOperationArgument.h>
#include <Ui/OperationArguments/Vector3OperationArgument.h>
#include <Ui/OperationArguments/FloatOperationArgument.h>
#include <Ui/OperationArguments/IntOperationArgument.h>

class CreatePrimitiveTool : public ToolbarTool {
public:
	GeometryPrimitives::GeometryPrimitive initial_primitive;
	CreatePrimitiveTool(GeometryPrimitives::GeometryPrimitive initial_primitive) {
		this->initial_primitive = initial_primitive;
	}

	OperationArgumentPanel create_panel(
		GeometryEditor* editor,
		std::function<void(AbstractGeometryOperation*)> done_callback,
		std::function<void()> cancel_callback
	) override {
		CreatePrimitiveOperation* create = new CreatePrimitiveOperation(
			*editor->get_current_geometry().lock().get(),
			editor->get_selection(),
			initial_primitive,
			{ 0.0f, 0.0f, 0.0f },
			1.0f
		);

		OperationArgumentPanel create_panel(create, done_callback, cancel_callback);
		create_panel.add_argument(new DropdownOperationArgument<GeometryPrimitives::GeometryPrimitive>(
			std::string("Primitive Type"), &create->primitive_type, {
				{ "Cube", GeometryPrimitives::Cube },
				{ "Cylinder", GeometryPrimitives::Cylinder },
				{ "UV Sphere", GeometryPrimitives::Sphere_Uv },
				{ "Torus", GeometryPrimitives::Torus },
				{ "Circle", GeometryPrimitives::Circle },
				{ "Plane", GeometryPrimitives::Plane },
				{ "Vertex", GeometryPrimitives::Vertex }
			}
		));
		create_panel.add_argument(new Vector3OperationArgument(std::string("Offset"), &create->position));
		create_panel.add_argument(new FloatOperationArgument(std::string("Diameter"), &create->diameter));
		create_panel.add_argument(new IntOperationArgument(std::string("Iterations"), &create->iterations));
		create_panel.add_argument(new IntOperationArgument(std::string("Segments"), &create->segments));
		create_panel.add_argument(new FloatOperationArgument(std::string("Height"), &create->height));
		create_panel.add_argument(new FloatOperationArgument(std::string("Hole"), &create->hole));
		return create_panel;
	}

	std::string get_name() {
		return "Create Primitive";
	}


	std::string get_tooltip() {
		return "Creates a new primitive shape";
	}
};