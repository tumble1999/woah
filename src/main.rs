mod operation;
mod parse_args;
mod parse_flags;
mod execute;

use operation::{Operation, FullOp};

fn main() -> Result<(), String> { // TODO: change error message formatting to just output directly
	let base_op = parse_args::parse(std::env::args())?;
	match base_op.operation {
		Operation::Help(op) => {
			print!(
				"{}",
				match op { // TODO: help messages
					None => "",
					Some(FullOp::Database) => "",
					Some(FullOp::Files) => "",
					Some(FullOp::Query) => "",
					Some(FullOp::Remove) => "",
					Some(FullOp::Sync) => "",
					Some(FullOp::Deptest) => "",
					Some(FullOp::Upgrade) => "",
				}
			);
		},
		Operation::Version => {
			// TODO
			print!("TODO");
		}
		Operation::Not(op) => {
			let complex_op = parse_flags::parse(op, base_op.args)?;
		},
	}

	Ok(())
}
