#!/usr/bin/perl

use Switch;
my @algorithms = ("spinlock", "pthread_lock", "control", "asymmetric", "asymmetric_var", "experiment", "experiment2", "experiment3", "experiment4", "queues", "message_passing");
my @options;

my $delay;
if(@ARGV >= 2)
{
	if($ARGV[0] eq "l")
	{
		@options = ("ef", "e", "sf", "s");
	}
	else
	{
		@options = ("nnpnnn", "nnpnn");#, "nnpn", "nn", "nf","n");
	}
	$delay = $ARGV[1];
}
else
{
	$delay = 0;
	@options = ("nnpnnn", "nnpnn", "nnpn", "nn", "nf","n");
}

my %arr;

foreach $option (@options)
{
	switch($option)
	{
		case "nnpnnn" { print "99.999% Dominance"; }
		case "nnpnn" { print "99.99% Dominance"; }
		case "nnpn" { print "99.9% Dominance"; }
		case "nn" { print "99% Dominance"; }
		case "nf" { print "95% Dominance"; }
		case "n" { print "90% Dominance"; }
		case "ef" { print "85% Dominance"; }
		case "e" { print "80% Dominance"; }
		case "sf" { print "75% Dominance"; }
		case "s" { print "70% Dominance"; }
	}

	print "\n";
	foreach $algorithm (@algorithms)
	{
		switch($algorithm)
		{
			case "spinlock" { print "Spinlock"; }
			case "pthread_lock" { print "Pthread Mutex"; }
			case "control" {print "Control"; }
			case "asymmetric" { print "Asymmetric (Vasuvedan)"; }
			case "asymmetric_var" { print "Asymmetric Variation"; }
			case "experiment" { print "Function Pointer Passing"; }
			case "experiment2" { print "Asynchronous Function Pointer Passing"; }
			case "experiment3" { print "Message Passing"; }
			case "experiment4" { print "Integrated Spinlock"; }
			case "queues" { print "Queue of Function Pointers"; }
			case "message_passing" { print "Queue of Messages"; }
		}
		print "\n";
		`make DELAY=$delay -C$algorithm $option`;
	
		$output = `./$algorithm/asymmetric`;
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
$machinename = `hostname -s`;
$num = `ls -l results|wc -l` + 1;

chomp($machinename);

$filename = $machinename."_delay".$delay."_".$ARGV[0]."_".$num;

print $filename;

open FILE, ">","results/$filename.gr" or die "WAT";

print FILE "=cluster;Spinlock(baseline);Pthread Mutex;Asymmetric(Vasuvedan);Asymmetric Variation;One Function Pointer;Asynchronous FP;Message Passing;FP Spinlock;Function Pointer Queue;Message Passing Queue;\n=table\nyformat=%gx\n=norotate\nylabel=Speedup\nxlabel=Dominance Percentage\n\n"; 


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
		case "nnpnnn" { print FILE "99.999"; }
		case "nnpnn" { print FILE "99.99"; }
		case "nnpn" { print FILE "99.9"; }
		case "nn" { print FILE "99"; }
		case "nf" { print FILE "95"; }
		case "n" { print FILE "90"; }
		case "ef" { print FILE "85"; }
		case "e" { print FILE "80"; }
		case "sf" { print FILE "75"; }
		case "s" { print FILE "70"; }
	}
	print FILE " ";
	foreach $algorithm (@algorithms)
	{
		if($algorithm ne "control")
		{
			if($arr{$algorithm}{$option} != 0)
			{
				print FILE $arr{"spinlock"}{$option}/$arr{$algorithm}{$option};
			}
			else
			{
				print FILE 0;
			}
			print FILE " ";
		}
	}
	print FILE "\n";
}
close FILE;

open FILE, ">","results/$filename.raw" or die "WAT";

foreach $algorithm (@algorithms)
{
	print FILE $algorithm;
	print FILE " ";
	foreach $option (@options)
	{
		print FILE $arr{$algorithm}{$option};
		print FILE " ";
	}	
	print FILE "\n";
}
close FILE;

print `perl ../bargraph.pl -png results/$filename.gr > graphs/$filename.png`;
