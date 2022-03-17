use crate::operation::NonHelpOp;

pub enum ComplexOperation {
	Version,
	Database(CommonOptions, DatabaseOptions),
	Files(CommonOptions, FilesOptions),
	Query(CommonOptions, QueryOptions),
	Remove(CommonOptions, RemoveOptions),
	Sync(CommonOptions, SyncOptions),
	Deptest(CommonOptions, DeptestOptions),
	Upgrade(CommonOptions, UpgradeOptions),
}
// TODO: set types and check what options are possible
// TODO: check for mistakes (options in or not in common, completely missing options)
pub struct CommonOptions {
	dbpath: Option<String>,
	root: Option<String>,
	quiet: bool,
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
	machinereadable: bool, // TODO: query doesn't have this
	noconfirm: bool,
	sysroot: Option<String>,
}
pub struct DatabaseOptions {
	check: /* enum */,
}
pub struct FilesOptions {
	list:
	regex:
	refresh:
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
pub struct DeptestOptions {
	check:
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

pub fn parse(operation: NonHelpOp, short_flags: Vec<char>, long_flags: Vec<String>) -> Result<ComplexOperation, String> {
	match operation {
		NonHelpOp::Version => Ok(ComplexOperation::Version),
		operation => {
			let common = CommonOptions {
				dbpath: None,
				arch: None,
				cachedir: None,
			}
			match operation {
				NonHelpOp::Database => {
					ComplexOperation::Database(common, )
				},
				NonHelpOp::Files => {
					ComplexOperation::Files(common, )
				},
				NonHelpOp::Query => {
					ComplexOperation::Query(common, )
				},
				NonHelpOp::Remove => {
					ComplexOperation::Remove(common, )
				},
				NonHelpOp::Sync => {
					ComplexOperation::Sync(common, )
				},
				NonHelpOp::Deptest => {
					ComplexOperation::Deptest(common, )
				},
				NonHelpOp::Upgrade => {
					ComplexOperation::Upgrade(common, )
				},
			}
		}
	}
}