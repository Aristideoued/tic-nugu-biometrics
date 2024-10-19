package com.neurotec.mma.samples;

import java.io.File;
import java.util.Optional;
import java.util.concurrent.TimeUnit;

import com.neurotec.mma.AcceleratorServiceGrpc;

import io.grpc.Grpc;
import io.grpc.ManagedChannel;
import io.grpc.ChannelCredentials;
import io.grpc.InsecureChannelCredentials;
import io.grpc.TlsChannelCredentials;

public class AcceleratorConnection implements AutoCloseable {
	ManagedChannel channel;
	AcceleratorServiceGrpc.AcceleratorServiceBlockingStub stub;

	public static AcceleratorConnection open(String target) throws Exception{
		ChannelCredentials channelCreds;
		if (Boolean.parseBoolean(System.getenv("TLS_ENABLE")) == true) {
			var tlsBuilder = TlsChannelCredentials.newBuilder();
			Optional.ofNullable(System.getenv("TLS_ROOT_CERT")).ifPresent(rootCertPath -> {
				try {
					tlsBuilder.trustManager(new File(rootCertPath)); // "/mnt/c/Branches/mma/install/certs/root.crt"));
				} catch (final Exception e) {
					throw new RuntimeException(e);
				}
			});
			channelCreds = tlsBuilder.build();
		}
		else {
			channelCreds = InsecureChannelCredentials.create();
		}

		var ipsConnection = new AcceleratorConnection();
		ipsConnection.channel = Grpc.newChannelBuilder(target, channelCreds).build();
		ipsConnection.stub = AcceleratorServiceGrpc.newBlockingStub(ipsConnection.channel);

		return ipsConnection;
	}

	@Override
	public void close() throws InterruptedException {
		if (channel != null) {
			channel.shutdown();
			channel.awaitTermination(10, TimeUnit.SECONDS);
		}
	}
	
	public AcceleratorServiceGrpc.AcceleratorServiceBlockingStub getStub() {
		return stub;
	}
}
