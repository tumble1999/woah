mod operation;
mod parse_args;
mod parse_flags;
mod execute;

use operation::{Operation, NonHelpOp};

fn main() -> Result<(), String> { // TODO: change error message formatting to just output directly
	let base_op = parse_args::parse(std::env::args())?;
	match base_op.operation {
		Operation::Help(op) => {
			print!(
				"{}",
				match op { // TODO: help messages
					None => "",
					Some(NonHelpOp::Version) => "",
					Some(NonHelpOp::Database) => "",
					Some(NonHelpOp::Files) => "",
					Some(NonHelpOp::Query) => "",
					Some(NonHelpOp::Remove) => "",
					Some(NonHelpOp::Sync) => "",
					Some(NonHelpOp::Deptest) => "",
					Some(NonHelpOp::Upgrade) => "",
				}
			)
		},
		Operation::Not(op) => {
			let complex_op = parse_flags::parse(op, base_op.short_flags, base_op.long_flags, base_op.targets)?;
		},
	}

	Ok(())
}
