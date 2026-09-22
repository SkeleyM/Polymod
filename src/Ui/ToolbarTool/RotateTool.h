#include <Ui/ToolbarTool.h>

#include <GeometryEditor.h>

#include <Geometry/Operations/RotateOperation.h>
#include <Ui/OperationArguments/Vector3OperationArgument.h>
#include <Ui/OperationArguments/FloatOperationArgument.h>

class RotateTool : public ToolbarTool {
public:
	OperationArgumentPanel create_panel(
		GeometryEditor* editor,
		std::function<void(AbstractGeometryOperation*)> done_callback,
		std::function<void()> cancel_callback
	) override {
		RotateOperation* rotate = new RotateOperation(*
			editor->get_current_geometry().lock().get(),
			editor->selection,
			{}, {}
		);

		OperationArgumentPanel rotate_panel(rotate, done_callback, cancel_callback);
		rotate_panel.add_argument(new FloatOperationArgument(std::string("Angle"), &rotate->angle));
		rotate_panel.add_argument(new Vector3OperationArgument(std::string("Axis"), &rotate->axis));
		return rotate_panel;
	}

	std::string get_name() {
		return "Rotate";
	}


	std::string get_tooltip() {
		return "Rotates the selection on the specified axis by an angle";
	}
};