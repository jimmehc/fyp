#!/usr/bin/perl

use Switch;
use Getopt::Std;

#filename,delay,long,execute,process,rawout,graphout,nondom,iterations
&getopts("f:d:lxprgni:");

print $opt_i;

#my @all_algorithms = ("SPL", "VAS", "VASVAR", "FP", "AFP", "MP", "AMP", "ISPL", "ISPLMP", "QFP", "MPQ", "FPR", "AFPR", "MPR", "AMPR","ISPLR", "ISPLMPR", "QFPR", "MPQR");
#my @all_algorithms = ("SPL", "MYSPL", "VAS", "VASVAR", "FP", "AFP", "MP", "AMP", "QFP", "MPQ", "FPR", "AFPR", "MPR", "AMPR","ISPLR", "ISPLMPR", "QFPR", "MPQR");
my @all_algorithms = ("SPL", "VAS", "VASVAR", "FP", "AFP", "MP", "AMP", "QFP", "MPQ");
my @algorithms_to_run = ("SPL", "VAS", "VASVAR", "FP", "AFP", "MP", "AMP", "ISPL", "ISPLMP", "QFP", "MPQ");
my @options;
my %arr;

my $delay;
if($opt_l)
{
		@options = ("EF", "E", "SF", "S");
}
else
{
	@options = ("100000", "10000", "1000");#, "100", "50", "25","10","5","4","3","2","1");
}

if($opt_d)
{
	$delay = $opt_d;
}
else
{
	$delay = 0;
}

$machinename = `hostname -s`;
$num = `ls -l results|wc -l` + 1;
chomp($machinename);

$filename = "PROGRESS_".$machinename."_delay".$delay."_".$num;

print $filename;
print "\n";

if($opt_x)
{
	&run_tests;
}
else
{
	if($opt_p)
	{
		&process_raw_data;
	}
	else
	{
		die "no data\n";
	}
}

if($opt_r)
{
	&raw_output;
}

if($opt_g)
{
	&output_dom_acc_graph_file;
	&make_graph;
}


sub run_tests
{
	foreach $option (@options)
	{
		switch($option)
		{
			case "100000" { print "99.999% Dominance"; }
			case "10000" { print "99.99% Dominance"; }
			case "1000" {print "99.9% Dominance"; }
			case "100" { print "99% Dominance"; }
			case "25" { print "95% Dominance"; }
			case "10" { print "90% Dominance"; }
			case "5" { print "80% Dominance"; }
		}

		print "\n";
		foreach $algorithm (@algorithms_to_run)
		{
			switch($algorithm)
			{
				case "SPL" { print "Spinlock"; }
				case "PTM" { print "Pthread Mutex"; }
				case "CTRL" {print "Control"; }
				case "VAS" { print "Asymmetric (Vasuvedan)"; }
				case "VASVAR" { print "Asymmetric Variation"; }
				case "FP" { print "Function Pointer Passing"; }
				case "AFP" { print "Asynchronous Function Pointer Passing"; }
				case "MP" { print "Message Passing"; }
				case "AMP" { print "Asynchronous Message Passing"; }
				case "ISPL" { print "Integrated Spinlock"; }
				case "ISPLMP" { print "Integrated Message Passing Spinlock"; }
				case "QFP" { print "Queue of Function Pointers"; }
				case "MPQ" { print "Queue of Messages"; }
				case "FPR" { print "Function Pointer Passing (Register)"; }
				case "AFPR" { print "Asynchronous Function Pointer Passing (Register)"; }
				case "MPR" { print "Message Passing (Register)"; }
				case "AMPR" { print "Asynchronous Message Passing (Register)"; }
				case "ISPLR" { print "Integrated Spinlock (Register)"; }
				case "ISPLMPR" { print "Integrated Message Passing Spinlock (Register)"; }
				case "QFPR" { print "Queue of Function Pointers (Register)"; }
				case "MPQR" { print "Queue of Messages (Register)"; }

			
			}
			print "\n";
			print `make progress NDD=$option ALG=$algorithm `;

			my @domres;
			my @nondomres;
			for($i = 0; $i < $opt_i; $i++)
			{
				$output = `./asymmetric`;
				$output =~ m/dom progress: (.*) a/;
				$domres[$i] = $1;
				$output =~ m/non-dom progress: (.*) a/;
				$nondomres[$i] = $1;
				print $output;
			}
			@domres = sort {$a <=> $b} @domres;
			@nondomres = sort {$a <=> $b} @nondomres;

			$mid = $opt_i/2;

			$arr{$algorithm}{$option}[0] = $domres[$mid];	
			$arr{$algorithm}{$option}[1] = $nondomres[$mid];
	
			print $arr{$algorithm}{$option}[0];
			print "\n";
			print $arr{$algorithm}{$option}[1];
			print "\n";
		}
		print "\n";

	}
}

sub process_raw_data
{
	open DATA, "<",$opt_f or die "WAT";

	my @lines = <DATA>;

	close DATA;

	foreach $line (@lines)
	{	
		@alginfo = split(/ /, $line);
		$algorithm = $alginfo[0];
		for($i = 1; $i < @alginfo; $i = $i + 3)
		{
			$arr{$algorithm}{$alginfo[$i]}[0] = $alginfo[$i+1];
			$arr{$algorithm}{$alginfo[$i]}[1] = $alginfo[$i+2];
		}
	}
}


#sub output_dom_acc_graph_file
#{
#	open FILE, ">","results/$filename.gr" or die "WAT";

#	print FILE "=cluster;";
	
#	foreach $algorithm (@all_algorithms)
#	{
#		switch($algorithm)
#		{
#			case "SPL" { print FILE "Spinlock;"; }
#			case "PTM" { print FILE "Pthread Mutex;"; }
#			case "CTRL" {print FILE "Control;"; }
#			case "VAS" { print FILE "Asymmetric (Vasuvedan);"; }
#			case "VASVAR" { print FILE "Asymmetric Variation;"; }
#			case "FP" { print FILE "Function Pointer Passing;"; }
#			case "AFP" { print FILE "Asynchronous Function Pointer Passing;"; }
#			case "MP" { print FILE "Message Passing;"; }
#			case "AMP" { print FILE "Asynchronous Message Passing;"; }
#			case "ISPL" { print FILE "Integrated Spinlock;"; }
#			case "ISPLMP" { print FILE "Integrated Message Passing Spinlock;"; }
#			case "QFP" { print FILE "Queue of Function Pointers;"; }
#			case "MPQ" { print FILE "Queue of Messages;"; }
#			case "FPR" { print FILE "Function Pointer Passing (Register);"; }
#			case "AFPR" { print FILE "Asynchronous Function Pointer Passing (Register);"; }
#			case "MPR" { print FILE "Message Passing (Register);"; }
#			case "AMPR" { print FILE "Asynchronous Message Passing (Register);"; }
#			case "ISPLR" { print FILE "Integrated Spinlock (Register);"; }
#			case "ISPLMPR" { print FILE "Integrated Message Passing Spinlock (Register);"; }
#			case "QFPR" { print FILE "Queue of Function Pointers (Register);"; }
#			case "MPQR" { print FILE "Queue of Messages (Register)"; }
#		}
#	}
#
#	print FILE "\n=table\nyformat=%g\n=norotate\nylabel=Speedup\nxlabel=Dominance\n\n"; 
#
#
#	print FILE "#";
#	foreach $algorithm (@all_algorithms)
#	{
#		print FILE $algorithm;
#		print FILE " ";
#	}
#
#	print FILE "\n";
#
#	foreach $option (@options)
#	{
#		switch($option)
#		{
#			case "100000" { print FILE "99.999"; }
#			case "10000" { print FILE "99.99"; }
#			case "1000" { print FILE "99.9"; }
#			case "100" { print FILE "99"; }
#			case "25" { print FILE "96"; }
#			case "10" { print FILE "90"; }
#			case "" { print FILE "85"; }
#			case "5" { print FILE "80"; }
#			case "SF" { print FILE "75"; }
#			case "S" { print FILE "70"; }
#		}
#		print FILE " ";
#		foreach $algorithm (@all_algorithms)
#		{
##		if($algorithm ne "control")
##		{
#				if($arr{"SPL"}{$option}[1] != 0)
#				{
#					print FILE $arr{$algorithm}{$option}[1]/$arr{"SPL"}{$option}[1];
#				}
#				else
#				{
#					print FILE 0;
#				}
#				print FILE " ";
##		}
#		}
#		print FILE "\n";
#	}
#	close FILE;
#}

sub output_graph_file
{


	open FILE, ">","results/$filename.gr" or die "WAT";

	print FILE "=stackcluster; Dom Accesses; Non-dom Accesses;";
	
	print FILE "\n=table\nyformat=%g%%\n=norotate\nylabel=Actual Access Percentage\nxlabel=Theoretical Dominance Percentage\n\n"; 

	print FILE "\n";

	foreach $option (@options)
	{
		print FILE "multimulti=";
		switch($option)
		{
			case "100000" { print FILE "99.999"; }
			case "10000" { print FILE "99.99"; }
			case "1000" { print FILE "99.9"; }
			case "100" { print FILE "99"; }
			case "25" { print FILE "95"; }
			case "10" { print FILE "90"; }
			case "5" { print "80"; }
		}
		print FILE "\n";
		foreach $algorithm (@all_algorithms)
		{
			print FILE $algorithm;
			print FILE " ";
			if($arr{$algorithm}{$option}[0] != 0)
			{
				print FILE ($arr{$algorithm}{$option}[0] * 100)/($arr{$algorithm}{$option}[0] + $arr{$algorithm}{$option}[1]);
				print FILE " ";
				print FILE ($arr{$algorithm}{$option}[1] * 100)/($arr{$algorithm}{$option}[0] + $arr{$algorithm}{$option}[1]);
			}
			else
			{
				print FILE 0;
			}
			print FILE "\n";
		}
		print FILE "\n";
	}
	close FILE;
}

sub raw_output
{
	open FILE, ">","results/$filename.raw" or die "WAT";

	foreach $algorithm (@algorithms_to_run)
	{
		print FILE $algorithm;
		print FILE " ";
		foreach $option (@options)
		{
			print FILE $option;
			print FILE " ";
			print FILE $arr{$algorithm}{$option}[0];
			print FILE " ";
			print FILE $arr{$algorithm}{$option}[1];
			print FILE " ";
		}	
		print FILE "\n";
	}
	close FILE;
}

#sub make_graph
#{
#	print `perl ../../bargraph.pl -png results/$filename.gr > graphs/$filename.png`;
#	print `scp graphs/$filename.png 134.226.38.27:~/results/.`;
#}

sub make_graph
{
#	print `perl ../../bargraph.pl -png results/$filename.gr > graphs/$filename.png`;
	print `scp results/$filename.gr 134.226.38.27:~/results/.`;
}


