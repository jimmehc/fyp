#!/usr/bin/perl

use Switch;
use Getopt::Std;

#filename,delay,long,execute,process,rawout,graphout
&getopts("f:d:lxprg");

my @algorithms = ("SPL", "VAS", "VASVAR", "FP", "AFP", "MP", "AMP", "QFP", "MPQ");
my @options;
my %arr;

my $delay;
if($opt_l)
{
		@options = ("EF", "E", "SF", "S");
}
else
{
	@options = ("NNPNNN", "NNPNN", "NNPN", "NN");#, "NF","N");
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

$filename = $machinename."_delay".$delay."_".$num;

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
	&output_graph_file;
	&make_graph;
}


sub run_tests
{
	foreach $option (@options)
	{
		switch($option)
		{
			case "NNPNNN" { print "99.999% Dominance"; }
			case "NNPNN" { print "99.99% Dominance"; }
			case "NNPN" { print "99.9% Dominance"; }
			case "NN" { print "99% Dominance"; }
			case "NF" { print "95% Dominance"; }
			case "N" { print "90% Dominance"; }
			case "EF" { print "85% Dominance"; }
			case "E" { print "80% Dominance"; }
			case "SF" { print "75% Dominance"; }
			case "S" { print "70% Dominance"; }
		}

		print "\n";
		foreach $algorithm (@algorithms)
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
				case "ISPL" { print "Integrated Spinlock"; }
				case "QFP" { print "Queue of Function Pointers"; }
				case "MPQ" { print "Queue of Messages"; }
			}
			print "\n";
			print `make DELAY=$delay ALG=$algorithm DOM=$option`;
		
			$output = `./asymmetric`;
			if($output =~ m/Tipping point/)
			{
				$arr{$algorithm}{$option} = 0;
			}
			else
			{
				$output =~ m/time: (.*)/;
				$arr{$algorithm}{$option} = $1;
			}
			print $arr{$algorithm}{$option};
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
		for($i = 1; $i < @alginfo; $i = $i + 2)
		{
			$arr{$algorithm}{$alginfo[$i]} = $alginfo[$i+1];
		}
	}
}



sub output_graph_file
{


	open FILE, ">","results/$filename.gr" or die "WAT";

	print FILE "=cluster;Spinlock(baseline);Asymmetric(Vasuvedan);Asymmetric Variation;One Function Pointer;Asynchronous FP;Message Passing;Function Pointer Queue;Message Passing Queue;\n=table\nyformat=%gx\n=norotate\nylabel=Speedup\nxlabel=Dominance Percentage\n\n"; 


	print FILE "#";
	foreach $algorithm (@algorithms)
	{
		print FILE $algorithm;
		print FILE " ";
	}

	print FILE "\n";

	foreach $option (@options)
	{
		switch($option)
		{
			case "NNPNNN" { print FILE "99.999"; }
			case "NNPNN" { print FILE "99.99"; }
			case "NNPN" { print FILE "99.9"; }
			case "NN" { print FILE "99"; }
			case "NF" { print FILE "95"; }
			case "N" { print FILE "90"; }
			case "EF" { print FILE "85"; }
			case "E" { print FILE "80"; }
			case "SF" { print FILE "75"; }
			case "S" { print FILE "70"; }
		}
		print FILE " ";
		foreach $algorithm (@algorithms)
		{
#		if($algorithm ne "control")
#		{
				if($arr{$algorithm}{$option} != 0)
				{
					print FILE $arr{"SPL"}{$option}/$arr{$algorithm}{$option};
				}
				else
				{
					print FILE 0;
				}
				print FILE " ";
#		}
		}
		print FILE "\n";
	}
	close FILE;
}

sub raw_output
{
	open FILE, ">","results/$filename.raw" or die "WAT";

	foreach $algorithm (@algorithms)
	{
		print FILE $algorithm;
		print FILE " ";
		foreach $option (@options)
		{
			print FILE $option;
			print FILE " ";
			print FILE $arr{$algorithm}{$option};
			print FILE " ";
		}	
		print FILE "\n";
	}
	close FILE;
}

sub make_graph
{
	print `perl ../../bargraph.pl -png results/$filename.gr > graphs/$filename.png`;
}



