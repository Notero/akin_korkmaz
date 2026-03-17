import { readdir, readFile } from 'node:fs/promises';
import { join } from 'node:path';

export async function buildFileSystemTree(targetPath) {
  const stats = await readdir(targetPath, { withFileTypes: true });

  // folder container
  const folderNode = {
    name: targetPath.split('/').pop() || targetPath,
    type: 'folder',
    children: []
  };

  for (const entry of stats) {
    const fullPath = join(targetPath, entry.name);

    if (entry.isDirectory()) {
      // go for the deeper folder 
      const childFolder = await buildFileSystemTree(fullPath);
      folderNode.children.push(childFolder);
    } else {
      // it's a file, just add it to the children
      folderNode.children.push({
        name: entry.name,
        type: 'file'
      });
    }
  }

  return folderNode;
}

export async function readFileContent(filePath) {
  try {
    const content = await readFile(filePath, 'utf-8');
    return content;
  } catch (error) {
    console.error(`Error reading file ${filePath}:`, error);
    throw error;
  }
}