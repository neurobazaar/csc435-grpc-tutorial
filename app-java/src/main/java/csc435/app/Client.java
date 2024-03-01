package csc435.app;

import csc435.app.MathFormulaGrpc.MathFormulaBlockingStub;
import io.grpc.Grpc;
import io.grpc.InsecureChannelCredentials;
import io.grpc.ManagedChannel;

public class Client {
    private String address;
    private String port;

    public Client(String address, String port) {
        this.address = address;
        this.port = port;
    }

    public void run() {
        String target = address + ":" + port;
        ManagedChannel channel = Grpc.newChannelBuilder(target, InsecureChannelCredentials.create()).build();
        MathFormulaBlockingStub stub = MathFormulaGrpc.newBlockingStub(channel);
        RequestMessage requestMessage;
        ReplyMessage replyMessage;

        requestMessage = RequestMessage.newBuilder().setMessage("addition").build();
        replyMessage = stub.getFormula(requestMessage);
        System.out.println(replyMessage.getMessage());

        requestMessage = RequestMessage.newBuilder().setMessage("multiplication").build();
        replyMessage = stub.getFormula(requestMessage);
        System.out.println(replyMessage.getMessage());

        requestMessage = RequestMessage.newBuilder().setMessage("quit").build();
        replyMessage = stub.getFormula(requestMessage);
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("USE: java Client <IP address> <port>");
            System.exit(1);
        }

        Client client = new Client(args[0], args[1]);
        client.run();
    }
}