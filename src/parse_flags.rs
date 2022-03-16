use crate::operation::Operation;
use crate::parse_args::BaseOperation;

pub struct ComplexOperation {
	pub operation: Operation,
	// TODO
	pub targets: Vec<String>,
}

pub fn parse(base_op: BaseOperation) -> Result<ComplexOperation, String> {
	match base_op.operation {
		_ => {return Err(String::from("TODO"));} // TODO
	}
	
	Ok(ComplexOperation {
		operation: base_op.operation,

		targets: base_op.targets,
	})
}