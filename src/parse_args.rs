use crate::operation::Operation;

pub struct BaseOperation { // TODO: better name
	pub operation: Operation,
	pub short_flags: Vec<char>,
	pub long_flags: Vec<String>,
	pub targets: Vec<String>,
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
					if operation.is_none() || matches!(o, Operation::Help) {
						operation = Some(o);
					} else {
						return Err(String::from("error: only one operation may be used at a time\n"));
					}
				} else {
					long_flags.push(String::from(trim));
				}
			} else {
				// short flag
				for f in a[1..].chars() {
					if let Ok(o) = Operation::from_short_arg(f) {
						if operation.is_none() || matches!(o, Operation::Help) {
							operation = Some(o);
						} else {
							return Err(String::from("error: only one operation may be used at a time\n"));
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
/* TODO
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