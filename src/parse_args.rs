pub enum Operation {
	Help,
	Version,
	Database,
	Files,
	Query,
	Remove,
	Sync,
	Deptest,
	Upgrade,
}

impl Operation {
	fn from_long_arg(flag: &str) -> Result<Operation, ()> {
		match flag {
			"help" => Ok(Operation::Help),
			"version" => Ok(Operation::Version),
			"database" => Ok(Operation::Database),
			"files" => Ok(Operation::Files),
			"query" => Ok(Operation::Query),
			"remove" => Ok(Operation::Remove),
			"sync" => Ok(Operation::Sync),
			"deptest" => Ok(Operation::Deptest),
			"upgrade" => Ok(Operation::Upgrade),
			_ => {Err(())}
		}
	}

	fn from_short_arg(flag: char) -> Result<Operation, ()> {
		match flag {
			'h' => Ok(Operation::Help),
			'V' => Ok(Operation::Version),
			'D' => Ok(Operation::Database),
			'F' => Ok(Operation::Files),
			'Q' => Ok(Operation::Query),
			'R' => Ok(Operation::Remove),
			'S' => Ok(Operation::Sync),
			'T' => Ok(Operation::Deptest),
			'U' => Ok(Operation::Upgrade),
			_ => {Err(())}
		}
	}
}

pub struct BaseOperation { // TODO: better name
	operation: Operation,
	short_flags: Vec<char>,
	long_flags: Vec<String>,
	targets: Vec<String>,
}

pub fn parse(mut args: std::env::Args) -> Result<BaseOperation, String> {
	let mut operation: Option<Operation> = None;
	let mut short_flags: Vec<char> = vec![];
	let mut long_flags: Vec<String> = vec![];
	let mut targets: Vec<String> = vec![];

	args.next();
	for a in args {
		if a.len() > 1 && a.as_bytes()[0] == b'-' {
			if a.as_bytes()[1] == b'-' {
				// long flag
				let trim = &a[2..];
				if let Ok(o) = Operation::from_long_arg(trim) {
					if operation.is_some() {
						return Err(String::from("error: only one operation may be used at a time\n"));
					} else {
						operation = Some(o);
					}
				} else {
					long_flags.push(String::from(trim));
				}
			} else {
				// short flag
				for f in a[1..].chars() {
					if let Ok(o) = Operation::from_short_arg(f) {
						if operation.is_some() {
							return Err(String::from("error: only one operation may be used at a time\n"));
						} else {
							operation = Some(o);
						}
					} else {
						short_flags.push(f);
					}
				}
			}
		} else {
			targets.push(a);
		}
	}
/*
	// MergeTargets
	args->targets_len += args->target_count; // Add spaces
	args->targets = (const char *)malloc(args->targets_len * sizeof(char));
	int offset = 0;
	for (int i = 0; i < args->target_count; i++) {
		int left = args->targets_len - offset,
			written = snprintf((char *)args->targets + offset, left, "%s ", args->targets_arr[i]);
			if (left < written)
				break;
			offset += written;
	}
	if (args->targets_len > 0 && DEBUG)
	printf("Targets: %s\n", args->targets);
*/
	if let Some(op) = operation {
		Ok(BaseOperation {
			operation: op,
			long_flags,
			short_flags,
			targets,
		})
	} else {
		Err(String::from("error: no operation specified (use -h for help)"))
	}
}