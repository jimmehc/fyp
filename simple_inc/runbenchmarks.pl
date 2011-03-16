#!/usr/bin/perl

#my @algorithms = ("spinlock", "control", "asymmetric", "experiment", "experiment2", "experiment3", "queues", "message_passing");
my @algorithms = ("asymmetric_var");
my @options = ("nnpnnn", "nnpnn", "nnpn", "nn", "n");
#my @options = ("n");


foreach $option (@options)
{
	print $option;
	print "\n";
	foreach $algorithm (@algorithms)
	{
		print $algorithm;
		print "\n";
		`make -C$algorithm $option`;
		print `./$algorithm/asymmetric`;
	}
}
