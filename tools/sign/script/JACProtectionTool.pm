##############################################################################
#
#  This module is to 
#
#  1) produce a JAC runtime configuration file.
#  2) optionally build Java signing project. 
#  3) execute the Java signing project.
#  4) deliver an Java voucher as a result in item 3).
#
#  It requires input parameters, 
#  
#  1) a configuration file in XML format.
#  2) a sub-operation type such as "build" or "no_build".
#
##############################################################################
package JACProtectionTool;

use IO::Handle;
use File::Temp;
use File::Basename;
use XML::Simple;
use Cwd qw(getcwd abs_path);

require Exporter;
@ISA =  qw(Exporter);

my $KEY_JAR_ID="java_archive_id";
my $KEY_NATIVE_LIB="native_lib_dir";
my $KEY_HMACSHA_HANDLE="hmacsha_handle";
my $HMACSHA_HANDLE_DEFAULT="YYT76H";
my $JAC_RUNTIME_CONFIG_FILE="JacConfigFile.txt";

my $jvmType;
my $platform;
my $projectHome;
my $JavaSigningToolHome;
my $JavaSigningConfigDeployPath="/data/app-private";
my $JavaVoucherDeployDir="./";
my $JACProtectionToolConfigFile;
my $nativeLibDirForJavaArchive;
my @JavaArchivingFiles = {};
my %statusMsg; 
my $operation; 
my $EXE = abs_path($0);

sub new {
    my ($class, $my_config_file, $opt) = @_;
    my $self = {
  	_app_config_file			=> $my_config_file,
        _operation  				=> $opt,
    };
    bless $self, $class;
    return $self;
}

sub executeCommand(){
    my ($self, $myCommand) = @_;
    print "Executing command: $myCommand\n";
    system($myCommand);
} 
sub initMsg {
    %statusMsg = (
	cf     	=> {yes => "Check: configuration file defined\n",
                    no  => "Check: invalid configuration file\n"},
	jsh 	=> {yes => "Check: valid Java Signing Tool Home\n",
		    no  => "Check: invalid Java Signing Tool Home\n"},
	jscdp	=> {yes => "Check: valid Java Sign config deploy directory\n",
		    no  => "Check: invalid Java Sign config deploy directory\n"},
	jarf	=> {yes => "Check: detect Java archiving file\n",
		    no  => "Check: no Java archiving file\n"},
	opr  	=> {yes => "Check: valid operational type\n",
		    no  => "Check: invalid operational type\n"},
    );
}

sub validate(){

    print "\nValidate variables\n";;
    if(defined($JACProtectionToolConfigFile)){
    	print ${$statusMsg{cf}}{yes};
    }else{
    	print ${$statusMsg{cf}}{no};
	exit(1);
    }
    if(defined($JavaSigningToolHome)){
    	print ${$statusMsg{jsh}}{yes};
    }else{
    	print ${$statusMsg{jsh}}{no};
	exit(2);
    }
    if(defined($JavaSigningConfigDeployPath)){
   	 print ${$statusMsg{jscdp}}{yes};
    }else{
        print ${$statusMsg{jscdp}}{no};
	exit(3);
    }
    my @fileArray = getFileNames();
    if( scalar(@fileArray)  > 0 ){
	print ${$statusMsg{jarf}}{yes};
    }else{
	print ${$statusMsg{jarf}}{no};
    }
    if(defined($operation) && 
	($operation =~ /build/  ||
	 $operation =~ /no_build/)){
	print ${$statusMsg{opr}}{yes};
    }else{
	print ${$statusMsg{opr}}{no};
	exit(4);
    }
}

sub parseXMLContents {
    no warnings 'uninitialized';
    my $xml = XML::Simple->new(SuppressEmpty => 1);
    my $data = $xml->XMLin($JACProtectionToolConfigFile);

    $jvmType = $data->{jvmType};
    $JavaSigningConfigDeployPath = $data->{javaSigningConfigDeployPath};
    $nativeLibDirForJavaArchive= $data->{javaArchiving}->{nativeLibDirForJavaArchive};
    $JavaVoucherDeployDir= $data->{javaSigning}->{outputFilePath};
    $JavaSigningToolHome = $data->{javaSigningToolHome};
    $myStr = $data->{javaArchiving}->{javaArchivingFiles};
    if($myStr =~ /^ARRAY\(0x/ || $myStr =~ /^HASH\(0x/){
    	@myArray = $data->{javaArchiving}->{javaArchivingFiles};
    	@JavaArchivingFiles = @{$myArray[0]{file}};
    }else{
	$JavaArchivingFiles[0] = $myStr;
    }
    foreach $myFile (@JavaArchivingFiles){
#    	print "Archiving file: $myFile\n";
    }
    $myStr = $data->{javaSigning}->{packageParameters}->{package};
    if($myStr =~ /^ARRAY\(0x/ ){
        @myArray = $data->{javaSigning}->{packageParameters};
    	@JavaArchiveFilesForSigning = @{$myArray[0]{package}};
    }else{
	$JavaArchiveFilesForSigning[0] = $myStr;
    }
    foreach $myFile (@JavaArchiveFilesForSigning) {
	print "Signing file: $myFile\n";
    }
}   

###########################################################################
#
#   Public function to initialize the application. This one has to be
#   called first.
#
###########################################################################
sub init {
    my($self) = @_;
    print "\nPerform initialization...\n";

    $projectHome = dirname($EXE);
    $JACProtectionToolConfigFile=$self->{_app_config_file};
    $operation = $self->{_operation}; 
    initMsg();
    parseXMLContents();
    validate();
}

sub getFileNames {
    my (@myFiles) = @_;
    my @myReturnArray = {};
    my $pos = 0;
    foreach $fileName (@JavaArchivingFiles){
   	if(defined($fileName)){
    	    my @myArray= split('/',$fileName);
	    $myReturnArray[$pos] = $myArray[$#myArray];
	    $pos++;
	}
    }
    return @myReturnArray;
}
sub parseFiles {
    my ($myFileStr) = @_;
    my @myArray = split(':',$myFileStr);
    chomp($myArray[$#myArray]);
    return @myArray;
}

sub configJavaSigningTool{
    my($self) = @_;
    print "\nDeliver configuration file on Android\n";
    my $myCommand =  "adb push "."$JACProtectionToolConfigFile "."$JavaSigningConfigDeployPath/irdeto_java_access_config.xml";
    $self->executeCommand($myCommand);
}

sub uninstallJavaSigningProcess {
    my($self) = @_;
    print "\nUninstall Java signing tool\n";
    my $myCommand = "adb uninstall com.irdeto.commandline.signing";
    $self->executeCommand($myCommand);
}
sub installJavaSigningTool{
    my($self) = @_;
    $self->uninstallJavaSigningProcess();
    print "\nInstall Java signing tool\n";
    if ($operation =~ /^build$/){ 
	print "my value $operation\n";
    	$myCommand = "cd $JavaSigningToolHome; ant install";
    }else{
    	$myCommand = "cd $JavaSigningToolHome/bin; adb install ./JACSigning-debug.apk";
    }
    $self->executeCommand($myCommand);
}

sub executeJavaSigningTool {
    my($self) = @_;
    print "\nExecute Java signing tool\n";
    print "Wait 30 seconds for Java sign to complete....\n";
    my $myCommand = "adb shell am start -a android.intent.action.MAIN -n com.irdeto.commandline.signing/com.irdeto.commandline.signing.JacSigningActivity";
    $self->executeCommand($myCommand);
    sleep(30);
}

sub harvestJavaVoucher {
    my($self) = @_;
    print "\nHarvest Java Voucher\n";
    my $myCommand = "adb pull "."$JavaVoucherDeployDir/"."irdeto_java_access.dat .";
    $self->executeCommand($myCommand);
}

##########################################################################
#  To create configuration file, JacConfigFile.txt to be stored in the
#  secure store
##########################################################################
sub prepareRuntimeConfigFile {
    my($self) = @_;
    print  "\nPrepare Runtime Configuration\n";
    my @fileArray = getFileNames();
    open FILE, ">", "$JAC_RUNTIME_CONFIG_FILE" or die $!;
#   print FILE "$KEY_HMACSHA_HANDLE $HMACSHA_HANDLE_DEFAULT\n";	
    foreach $fileName (@fileArray){
        if(defined($fileName)){
	    print FILE "$KEY_JAR_ID $fileName\n";	
	}
    }
    if(defined($nativeLibDirForJavaArchive) &&  
	       $nativeLibDirForJavaArchive !~ /^HASH\(0x/ ){
	print FILE "$KEY_NATIVE_LIB $nativeLibDirForJavaArchive\n";   
    }
    close FILE;
}


###########################################################################
#
#   Public function to kick off Java Signing process and retrieve Java 
#   voucher
#
###########################################################################
sub execute{
    my ($self) =@_;
    $self->prepareRuntimeConfigFile();
    $self->configJavaSigningTool();
    $self->installJavaSigningTool();
    $self->executeJavaSigningTool();
    $self->harvestJavaVoucher();
}
1;
