package csc435.app;

import java.io.IOException;
import java.util.Scanner;

import io.grpc.Grpc;
import io.grpc.InsecureServerCredentials;
import io.grpc.ServerBuilder;
import io.grpc.stub.StreamObserver;

public class Server {
    private Integer port;
    private io.grpc.Server server;

    public Server(String port) {
        this.port = Integer.parseInt(port);
    }

    public void run() {
        ServerBuilder<?> serverBuilder = Grpc.newServerBuilderForPort(port, InsecureServerCredentials.create());
        server = serverBuilder.addService(new MathFormulaService()).build();
        
        try {
            server.start();
        } catch (IOException e) {
            return;
        }
        
        Thread thread = new Thread(new WaitForQuit());
        thread.start();

        try {
            server.awaitTermination();
        } catch (InterruptedException e) { }

        try {
            server.awaitTermination();
        } catch (InterruptedException e) { }
    }

    private static class MathFormulaService extends MathFormulaGrpc.MathFormulaImplBase {
        
        @Override
        public void getFormula(RequestMessage requestMessage, StreamObserver<ReplyMessage> respObserver) {
            respObserver.onNext(buildFormula(requestMessage));
            respObserver.onCompleted();
        }

        private ReplyMessage buildFormula(RequestMessage requestMessage) {
            if (requestMessage.getMessage().compareTo("addition") == 0) {
                return ReplyMessage.newBuilder().setMessage("2+2=4").build();
            }

            if (requestMessage.getMessage().compareTo("multiplication") == 0) {
                return ReplyMessage.newBuilder().setMessage("2x2=4").build();
            }

            return ReplyMessage.newBuilder().setMessage("???").build();
        }
    }

    private class WaitForQuit implements Runnable {

        @Override
        public void run() {
            Scanner sc = new Scanner(System.in);

            String command;

            while (true) {
                System.out.print("> ");
                
                command = sc.nextLine();
                
                if (command.compareTo("quit") == 0) {
                    server.shutdownNow();
                    System.out.println("Server terminated!");
                    break;
                }
            }

            sc.close();
        }
        
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("USE: java Server <IP address> <port>");
            System.exit(1);
        }

        Server server = new Server(args[1]);
        server.run();
    }
}