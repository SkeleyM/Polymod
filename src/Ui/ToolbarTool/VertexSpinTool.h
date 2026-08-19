#include <Ui/ToolbarTool.h>

#include <GeometryEditor.h>

#include <Geometry/Operations/VertexSpinOperation.h>
#include <Ui/OperationArguments/Vector3OperationArgument.h>;
#include <Ui/OperationArguments/FloatOperationArgument.h>;
#include <Ui/OperationArguments/IntOperationArgument.h>;

class VertexSpinTool : public ToolbarTool {
public:

	OperationArgumentPanel create_panel(GeometryEditor* editor, std::function<void(AbstractGeometryOperation*)> done_callback) override {
		VertexSpinOperation* spin = new VertexSpinOperation(*
			editor->get_current_geometry().lock().get(),
			editor->selection,
			{}, {}, {}, {}
		);

		OperationArgumentPanel spin_panel(spin, done_callback);
		spin_panel.add_argument(new IntOperationArgument(std::string("Samples"), &spin->samples));
		spin_panel.add_argument(new FloatOperationArgument(std::string("Angle"), &spin->angle_x));
		spin_panel.add_argument(new Vector3OperationArgument(std::string("Origin"), &spin->origin));
		return spin_panel;
	}

	std::string get_name() {
		return "Spin";
	}
};