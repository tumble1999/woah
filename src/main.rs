mod parse_args;

fn main() -> Result<(), String> { // TODO: change error message formatting to just output directly
	let base_op = parse_args::parse(std::env::args())?;

	Ok(())
}
