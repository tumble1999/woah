use crate::operation::Operation;

pub enum Argument {
	Short(char),
	Long(String),
	Other(String), // targets or parameters
	Seperator, // indicates that some other flag used to be here, used to stop "-a -b b -a" from being accepted because -b was parsed before -a
}

// NOTE: strings after flags MAY be flag parameters but they may be targets, parsing on them needs to be done later in processing
pub struct BaseOperation { // TODO: better name
	pub operation: Operation,
	pub args: Vec<Argument>,
}

pub fn parse(mut args: std::env::Args) -> Result<BaseOperation, String> {
	let mut operation: Option<Operation> = None;
	let mut out_args: Vec<Argument> = vec![];

	args.next();
	for a in args {
		if a.len() > 1 && a.as_bytes()[0] == b'-' {
			if a.as_bytes()[1] == b'-' {
				// long flag
				let trim = &a[2..];
				if let Ok(new) = Operation::from_long_arg(trim) {
					operation = get_new_op(operation, new)?;
					out_args.push(Argument::Seperator);
				} else {
					out_args.push(Argument::Long(String::from(trim)));
				}
			} else {
				// short flag
				for f in a[1..].chars() {
					if let Ok(new) = Operation::from_short_arg(f) {
						operation = get_new_op(operation, new)?;
						out_args.push(Argument::Seperator);
					} else {
						out_args.push(Argument::Short(f));
					}
				}
			}
		} else {
			out_args.push(Argument::Other(a));
		}
	}

	if let Some(op) = operation {
		Ok(BaseOperation {
			operation: op,
			args: out_args,
		})
	} else {
		Err(String::from("error: no operation specified (use -h for help)"))
	}
}

fn get_new_op(curr: Option<Operation>, new: Operation) -> Result<Option<Operation>, String> {
	if curr.is_none() {
		Ok(Some(new))
	} else if matches!(new, Operation::Help(_)) {
		if let Some(Operation::Not(nh)) = curr {
			Ok(Some(Operation::Help(Some(nh))))
		} else {
			Ok(curr)
		}
	} else {
		Err(String::from("error: only one operation may be used at a time\n"))
	}
}