mod operation;
mod parse_args;
mod parse_flags;
mod execute;

fn main() -> Result<(), String> { // TODO: change error message formatting to just output directly
	let base_op = parse_args::parse(std::env::args())?;
	let complex_op = parse_flags::parse(base_op)?;

	Ok(())
}
