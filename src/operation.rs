pub enum Operation {
	Help(Option<NonHelpOp>),
	Not(NonHelpOp),
}
pub enum NonHelpOp {
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
	pub fn from_long_arg(flag: &str) -> Result<Operation, ()> {
		match flag {
			"help" => Ok(Operation::Help(None)),
			"version" => Ok(Operation::Not(NonHelpOp::Version)),
			"database" => Ok(Operation::Not(NonHelpOp::Database)),
			"files" => Ok(Operation::Not(NonHelpOp::Files)),
			"query" => Ok(Operation::Not(NonHelpOp::Query)),
			"remove" => Ok(Operation::Not(NonHelpOp::Remove)),
			"sync" => Ok(Operation::Not(NonHelpOp::Sync)),
			"deptest" => Ok(Operation::Not(NonHelpOp::Deptest)),
			"upgrade" => Ok(Operation::Not(NonHelpOp::Upgrade)),
			_ => Err(())
		}
	}
	pub fn from_short_arg(flag: char) -> Result<Operation, ()> {
		match flag {
			'h' => Ok(Operation::Help(None)),
			'V' => Ok(Operation::Not(NonHelpOp::Version)),
			'D' => Ok(Operation::Not(NonHelpOp::Database)),
			'F' => Ok(Operation::Not(NonHelpOp::Files)),
			'Q' => Ok(Operation::Not(NonHelpOp::Query)),
			'R' => Ok(Operation::Not(NonHelpOp::Remove)),
			'S' => Ok(Operation::Not(NonHelpOp::Sync)),
			'T' => Ok(Operation::Not(NonHelpOp::Deptest)),
			'U' => Ok(Operation::Not(NonHelpOp::Upgrade)),
			_ => Err(())
		}
	}
}