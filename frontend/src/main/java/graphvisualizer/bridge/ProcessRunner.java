package graphvisualizer.bridge;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.List;

public class ProcessRunner {
    private final String executablePath;
    private String errorMessage = "";

    public ProcessRunner(String executablePath){
        this.executablePath = executablePath;
    }

    public int run(File inputFile, File outputFile, String algorithm) throws Exception{
        boolean isWindows = System.getProperty("os.name").toLowerCase().contains("win");
        
        List<String> command;
        if (isWindows) {
            File exeFile = new File(executablePath + ".exe");
            if (exeFile.exists()) {
                command = List.of(
                        exeFile.getAbsolutePath(),
                        "-i", inputFile.getAbsolutePath(),
                        "-o", outputFile.getAbsolutePath(),
                        "-a", algorithm,
                        "-f", "bin"
                );
            } else {
                String wslExecutable = "./" + executablePath.replace('\\', '/');
                String wslInputPath = convertToWslPath(inputFile.getAbsolutePath());
                String wslOutputPath = convertToWslPath(outputFile.getAbsolutePath());
                
                command = List.of(
                        "wsl",
                        wslExecutable,
                        "-i", wslInputPath,
                        "-o", wslOutputPath,
                        "-a", algorithm,
                        "-f", "bin"
                );
            }
        } else {
            command = List.of(
                    executablePath,
                    "-i", inputFile.getAbsolutePath(),
                    "-o", outputFile.getAbsolutePath(),
                    "-a", algorithm,
                    "-f", "bin"
            );
        }

        ProcessBuilder pb = new ProcessBuilder(command);
        Process process = pb.start();

        StringBuilder errorBuilder = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getErrorStream(), StandardCharsets.UTF_8))){
            String line;
            while ((line = reader.readLine()) != null) {
                errorBuilder.append(line).append("\n");
            }
        }

        int exitCode = process.waitFor();
        this.errorMessage = errorBuilder.toString().trim();

        return exitCode;
    }

    private String convertToWslPath(String windowsPath) {
        if (windowsPath == null) return null;
        if (windowsPath.length() >= 2 && windowsPath.charAt(1) == ':') {
            char drive = Character.toLowerCase(windowsPath.charAt(0));
            String rest = windowsPath.substring(2).replace('\\', '/');
            return "/mnt/" + drive + rest;
        }
        return windowsPath.replace('\\', '/');
    }

    public String getErrorMessage(){
        return errorMessage;
    }
}
