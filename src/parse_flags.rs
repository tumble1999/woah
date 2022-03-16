use crate::operation::NonHelpOp;
use crate::parse_args::BaseOperation;

pub struct ComplexOperation {
	pub operation: Operation,
	// TODO
	pub targets: Vec<String>,
}

pub fn parse(operation: NonHelpOp, short_flags: Vec<char>, long_flags: Vec<String>, targets: Vec<String>) -> Result<ComplexOperation, String> {
	match operation {
		_ => {return Err(String::from("TODO"));} // TODO
	}
	
	Ok(ComplexOperation {
		operation,

		targets,
	})
}