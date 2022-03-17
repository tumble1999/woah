pub enum Operation {
	Help(Option<FullOp>),
	Version,
	Not(FullOp),
}
// operations that actually use parameters given unline help and version
pub enum FullOp {
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
			"version" => Ok(Operation::Version),
			"database" => Ok(Operation::Not(FullOp::Database)),
			"files" => Ok(Operation::Not(FullOp::Files)),
			"query" => Ok(Operation::Not(FullOp::Query)),
			"remove" => Ok(Operation::Not(FullOp::Remove)),
			"sync" => Ok(Operation::Not(FullOp::Sync)),
			"deptest" => Ok(Operation::Not(FullOp::Deptest)),
			"upgrade" => Ok(Operation::Not(FullOp::Upgrade)),
			_ => Err(())
		}
	}
	pub fn from_short_arg(flag: char) -> Result<Operation, ()> {
		match flag {
			'h' => Ok(Operation::Help(None)),
			'V' => Ok(Operation::Version),
			'D' => Ok(Operation::Not(FullOp::Database)),
			'F' => Ok(Operation::Not(FullOp::Files)),
			'Q' => Ok(Operation::Not(FullOp::Query)),
			'R' => Ok(Operation::Not(FullOp::Remove)),
			'S' => Ok(Operation::Not(FullOp::Sync)),
			'T' => Ok(Operation::Not(FullOp::Deptest)),
			'U' => Ok(Operation::Not(FullOp::Upgrade)),
			_ => Err(())
		}
	}
}