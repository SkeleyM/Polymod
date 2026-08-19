#include <Ui/ToolbarTool.h>

#include <GeometryEditor.h>

#include <Geometry/Operations/ScaleOperation.h>
#include <Ui/OperationArguments/Vector3OperationArgument.h>;
#include <Ui/OperationArguments/FloatOperationArgument.h>;

class ScaleTool : public ToolbarTool {
public:
	OperationArgumentPanel create_panel(GeometryEditor* editor, std::function<void(AbstractGeometryOperation*)> done_callback) override {
		ScaleOperation* scale = new ScaleOperation(*
			editor->get_current_geometry().lock().get(),
			editor->selection,
			{}
		);

		OperationArgumentPanel scale_panel(scale, done_callback);
		scale_panel.add_argument(new Vector3OperationArgument(std::string("Scale"), &scale->scale));
		return scale_panel;
	}

	std::string get_name() {
		return "Scale";
	}
};