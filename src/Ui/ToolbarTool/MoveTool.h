#include <Ui/ToolbarTool.h>

#include <GeometryEditor.h>

#include <Geometry/Operations/MoveOperation.h>
#include <Ui/OperationArguments/Vector3OperationArgument.h>

class MoveTool : public ToolbarTool {
public:
	OperationArgumentPanel create_panel(GeometryEditor* editor, std::function<void(AbstractGeometryOperation*)> done_callback) override {
		MoveOperation* move = new MoveOperation(*
			editor->get_current_geometry().lock().get(),
			editor->selection,
			{}
		);

		OperationArgumentPanel move_panel(move, done_callback);
		move_panel.add_argument(new Vector3OperationArgument(std::string("Offset"), &move->offset));
		return move_panel;
	}

	std::string get_name() {
		return "Move";
	}
};