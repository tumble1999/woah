use crate::operation::FullOp;
use crate::parse_args::Argument;

pub enum ComplexOperation {
	Database(CommonOptions, DatabaseOptions),
	Files(CommonOptions, FilesOptions),
	Query(CommonOptions, QueryOptions),
	Remove(CommonOptions, RemoveOptions),
	Sync(CommonOptions, SyncOptions),
	Deptest(CommonOptions),
	Upgrade(CommonOptions, UpgradeOptions),
}
// TODO: set types and check what options are possible
// TODO: check for mistakes (options in or not in common, completely missing options)
pub struct CommonOptions {
	dbpath: Option<String>,
	quiet: bool,
	root: Option<String>,
	verbose: bool,
	arch: Option<String>,
	cachedir: Option<String>,
	color: bool,
	config: Option<String>,
	confirm: bool,
	debug: bool,
	disable_download_timeout: bool,
	gpgdir: Option<String>,
	hookdir: Option<String>,
	logfile: Option<String>,
	noconfirm: bool,
	sysroot: Option<String>,
}
pub struct DatabaseOptions {
	check: /* enum */,
	asdeps:
	asexplicit:
}
pub struct FilesOptions {
	list:
	regex:
	refresh:
	machinereadable: bool,
}
pub struct QueryOptions {
	changelog:
	deps:
	explicit:
	groups:
	info:
	check:
	list:
	foreign:
	native:
	owns: Option<String>,
	file: Option<String>,
	search: bool,
	unrequired: /* enum */,
	upgrades: bool
}
pub struct RemoveOptions {
	cascade: bool,
	nodeps:
	nosave: bool,
	print: bool,
	recursive:
	unneeded: bool,
	assume_installed:
	dbonly: bool,
	noprogressbar: bool,
	noscriptlet: bool,
	print_format: Option<String>,
}
pub struct SyncOptions {
	clean:
	nodeps:
	groups:
	info:
	list: Option<String>,
	print: bool,
	search: bool,
	sysupgrade:
	downloadonly: bool,
	refresh:
	asdeps:
	asexplicit:
	assume_installed:
	dbonly:
	ignore: Vec<String>,
	ignoregroup: Vec<String>,
	needed:
	noprogressbar:
	noscriptlet:
	overwrite: Vec<String>,
	print_format: Option<String>,
}
pub struct UpgradeOptions {
	nodeps:
	print: bool,
	downloadonly: bool,
	asdeps:
	asexplicit:
	assume_installed:
	dbonly:
	ignore: Vec<String>,
	ignoregroup: Vec<String>,
	needed:
	noprogressbar:
	noscriptlet:
	overwrite: Vec<String>,
	print_format: Option<String>,
}

pub struct ComplexFormula { // TODO: better name
	pub operation: ComplexOperation,
	pub targets: Vec<String>,
}

pub fn parse(operation: FullOp, mut args: Vec<Argument>) -> Result<ComplexFormula, String> {
	let targets : Vec<String> = vec![];
	let common = CommonOptions {
		dbpath: None,
		arch: None,
		cachedir: None,
	};
	args.retain(|arg| {
		match arg {
			Argument::Short('') | Argument::Long(String::from("")) => {},
			_ => {return true;},
		}
		false
	});

	let out_operation = match operation {
		FullOp::Database => {
			ComplexOperation::Database(common, )
		},
		FullOp::Files => {
			ComplexOperation::Files(common, )
		},
		FullOp::Query => {
			ComplexOperation::Query(common, )
		},
		FullOp::Remove => {
			ComplexOperation::Remove(common, )
		},
		FullOp::Sync => {
			ComplexOperation::Sync(common, )
		},
		FullOp::Deptest => ComplexOperation::Deptest(common),
		FullOp::Upgrade => {
			ComplexOperation::Upgrade(common, )
		},
	};
	ComplexFormula {
		operation: out_operation,
		targets,
	}
}