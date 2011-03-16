#!/usr/bin/perl

#my @algorithms = ("spinlock", "control", "asymmetric", "experiment", "queues", "message_passing");
my @algorithms = ("queues");
#my @options = ("nnpnnn", "nnpnn", "nnpn", "nn", "n");
my @options = ("n");


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
