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
	pub fn from_long_arg(flag: &str) -> Result<Operation, ()> {
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
			_ => Err(())
		}
	}
	pub fn from_short_arg(flag: char) -> Result<Operation, ()> {
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
			_ => Err(())
		}
	}
}