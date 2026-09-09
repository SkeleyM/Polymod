#include <Ui/ToolbarTool.h>

#include <GeometryEditor.h>

#include <Geometry/Operations/ExtrudeOperation.h>
#include <Ui/OperationArguments/Vector3OperationArgument.h>

class ExtrudeTool : public ToolbarTool {
public:
	OperationArgumentPanel create_panel(GeometryEditor* editor, std::function<void(AbstractGeometryOperation*)> done_callback) override {
		ExtrudeOperation* extrude = new ExtrudeOperation(*
			editor->get_current_geometry().lock().get(),
			editor->selection,
			{}
		);

		OperationArgumentPanel extrude_panel(extrude, done_callback);
		extrude_panel.add_argument(new Vector3OperationArgument(std::string("Extrude Direction"), &extrude->extrusion));
		return extrude_panel;
	}

	std::string get_name() {
		return "Extrude";
	}
};