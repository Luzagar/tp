const vscode = require('vscode');
const path = require('path');
const fs = require('fs');

function activate(context) {
    const exe = process.platform === 'win32' ? 'penumbra.exe' : 'penumbra';
    context.subscriptions.push(
        vscode.debug.registerDebugAdapterDescriptorFactory('penumbra', {
            createDebugAdapterDescriptor(_session) {
                // Look for penumbra in build/binutils/ (downloaded by build system)
                const workspaceFolder = vscode.workspace.workspaceFolders?.[0]?.uri.fsPath;
                if (workspaceFolder) {
                    const buildPath = path.join(workspaceFolder, 'build', 'binutils', exe);
                    if (fs.existsSync(buildPath)) {
                        return new vscode.DebugAdapterExecutable(buildPath, ['--dap']);
                    }
                }

                // Fallback to PATH
                return new vscode.DebugAdapterExecutable(exe, ['--dap']);
            }
        })
    );
}

function deactivate() {}

module.exports = { activate, deactivate };
