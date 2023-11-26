import "./style.css";

const app: HTMLDivElement = document.querySelector("#app")!;

let currentSticker: string | null = null;
let currentColor = "black";
const stickerButton: HTMLButtonElement[] = [];
let colorCounter = 0;
const numColors = 5;

class CursorCommand {
  x: number;
  y: number;
  cursorSticker: string;
  color: string;
  constructor(x: number, y: number, cursorSticker: string, color: string) {
    this.x = x;
    this.y = y;
    this.cursorSticker = cursorSticker;
    this.color = color;
  }
  execute() {
    ctx.fillStyle = this.color;
    ctx.font = `${cursorSize}px monospace`;
    const xShift = 8;
    const yShift = 16;

    ctx.fillText(`${this.cursorSticker}`, this.x - xShift, this.y + yShift);
  }
}

interface DrawingCommand {
  execute(ctx: CanvasRenderingContext2D): void;
  drag(x: number, y: number): void;
}

class Sticker implements DrawingCommand {
  cursorSticker: string;
  x: number;
  y: number;
  stickerSize: number;
  stickerColor: string;
  constructor(
    x: number,
    y: number,
    cursorSticker: string,
    stickerSize: number,
    stickerColor: string,
  ) {
    this.cursorSticker = cursorSticker;
    this.x = x;
    this.y = y;
    this.stickerSize = stickerSize;
    this.stickerColor = stickerColor;
  }
  execute(ctx: CanvasRenderingContext2D) {
    ctx.fillStyle = this.stickerColor;
    ctx.font = `${this.stickerSize}px monospace`;
    ctx.fillText(this.cursorSticker, this.x, this.y);
  }
  drag(x: number, y: number) {
    this.x = x;
    this.y = y;
  }
}

class LineCommand implements DrawingCommand {
  points: { x: number; y: number }[];
  thickness: number;
  color: string;
  constructor(x: number, y: number, thickness: number, color: string) {
    //remove sticker, also just hold x and y rather than a point
    this.points = [{ x, y }];
    this.thickness = thickness;
    this.color = color;
  }
  execute(ctx: CanvasRenderingContext2D) {
    ctx.strokeStyle = this.color;
    ctx.lineWidth = this.thickness;
    ctx.beginPath();
    // eslint-disable-next-line @typescript-eslint/no-magic-numbers
    const { x, y } = this.points[0];
    ctx.moveTo(x, y);
    for (const { x, y } of this.points) {
      ctx.lineTo(x, y);
    }
    ctx.stroke();
  }
  drag(x: number, y: number) {
    this.points.push({ x, y });
  }
}

enum ButtonName {
  clear = "clear",
  undo = "undo",
  redo = "redo",
  thin = "thin",
  thick = "thick",
  color = "color",
}

interface Buttons {
  button: HTMLButtonElement;
  buttonText: ButtonName;
}

const tools: Buttons[] = Object.values(ButtonName).map((buttonText) => {
  return {
    button: document.createElement("button"),
    buttonText,
  };
});

const exportButton = document.createElement("button");
exportButton.innerHTML = "export";
app.append(exportButton);

const stickers: string[] = ["💀", "🎃", "👻", "custom sticker"];
const colors: string[] = ["black", "orange", "green", "red", "blue"];

const canvas: HTMLCanvasElement = document.createElement("canvas");
canvas.height = 256;
canvas.width = 256;
const ctx = canvas.getContext("2d")!;
app.append(canvas);

createButtons(tools); //create all the clickable non-sticker buttons

for (const sticker of stickers) {
  createStickerButtons(sticker);
}

const bus = new EventTarget();

type EventName = "drawing-changed" | "tool-moved";
function notify(name: EventName) {
  bus.dispatchEvent(new Event(name));
}

const commands: DrawingCommand[] = [];
const redoCommands: DrawingCommand[] = [];
let currentStickerCommand: Sticker | null = null;

let lineWidth = 4;
let cursorSize = 32;
const STICKER_SIZE = 32;

let cursorCommand: CursorCommand | null = null;

bus.addEventListener("drawing-changed", redraw);
bus.addEventListener("tool-moved", redraw);

let currentLineCommand: LineCommand | null = null;

const toolClickHandlers: Record<ButtonName, () => void> = {
  clear() {
    // eslint-disable-next-line @typescript-eslint/no-magic-numbers
    commands.splice(0, commands.length);
    notify("drawing-changed");
  },
  undo() {
    const lastAction = commands.pop();
    if (lastAction) {
      redoCommands.push(lastAction);
      notify("drawing-changed");
    }
  },
  redo() {
    const lastAction = redoCommands.pop();
    if (lastAction) {
      commands.push(lastAction);
      notify("drawing-changed");
    }
  },
  thin() {
    currentSticker = "*";
    lineWidth = THIN_WIDTH;
    cursorSize = lineWidth * CURSOR_SIZE_BOOST;
    colorCounter = getRandomInt(numColors);
    currentColor = colors[colorCounter];
  },
  thick() {
    currentSticker = "*";
    lineWidth = THICK_WIDTH;
    cursorSize = lineWidth * CURSOR_SIZE_BOOST;
    colorCounter = getRandomInt(numColors);
    currentColor = colors[colorCounter];
  },
  color() {
    // eslint-disable-next-line @typescript-eslint/no-magic-numbers
    console.log(colorCounter);
    // eslint-disable-next-line @typescript-eslint/no-magic-numbers
    colorCounter += 1;
    if (colorCounter == numColors) {
      // eslint-disable-next-line @typescript-eslint/no-magic-numbers
      colorCounter = 0;
    }

    currentColor = colors[colorCounter];
  },
};

for (const tool of tools) {
  tool.button.addEventListener("click", toolClickHandlers[tool.buttonText]);
}

for (const stickerbutton of stickerButton) {
  listenCustomSticker(stickerbutton);
}

exportButton.addEventListener("click", exportListener);

//https://shoddy-paint.glitch.me/paint0.html
canvas.addEventListener("mousedown", (e) => {
  cursorCommand = null;
  if (currentSticker && currentSticker != "*") {
    currentStickerCommand = new Sticker(
      e.offsetX,
      e.offsetY,
      currentSticker,
      STICKER_SIZE,
      currentColor,
    );
    commands.push(currentStickerCommand);
    // eslint-disable-next-line @typescript-eslint/no-magic-numbers
    redoCommands.splice(0, redoCommands.length);
    notify("drawing-changed");
  } else if (currentSticker == "*") {
    currentLineCommand = new LineCommand(
      e.offsetX,
      e.offsetY,
      lineWidth,
      currentColor,
    );
    commands.push(currentLineCommand);
    // eslint-disable-next-line @typescript-eslint/no-magic-numbers
    redoCommands.splice(0, redoCommands.length);
    notify("drawing-changed");
  }
});

canvas.addEventListener("mousemove", (e) => {
  if (currentSticker) {
    cursorCommand = new CursorCommand(
      e.offsetX,
      e.offsetY,
      currentSticker,
      currentColor,
    );
  }
  notify("tool-moved");

  // eslint-disable-next-line @typescript-eslint/no-magic-numbers
  if (e.buttons == 1) {
    cursorCommand = null;
    if (currentSticker == "*") {
      currentLineCommand?.drag(e.offsetX, e.offsetY);
    } else if (currentSticker != "*") {
      currentStickerCommand?.drag(e.offsetX, e.offsetY);
    }
    notify("drawing-changed");
  }
});

canvas.addEventListener("mouseup", (e) => {
  if (currentSticker) {
    currentLineCommand = null;
    cursorCommand = new CursorCommand(
      e.offsetX,
      e.offsetY,
      currentSticker,
      currentColor,
    );
    notify("drawing-changed");
  }
});

canvas.addEventListener("mouseout", () => {
  cursorCommand = null;
  notify("tool-moved");
});

canvas.addEventListener("mouseenter", (e) => {
  if (currentSticker == "*") {
    cursorCommand = new CursorCommand(
      e.offsetX,
      e.offsetY,
      currentSticker,
      currentColor,
    );
  }
  notify("tool-moved");
});

const CURSOR_SIZE_BOOST = 6;
const THIN_WIDTH = 2;
const THICK_WIDTH = 6;

function eventListenerSticker(str: string) {
  currentSticker = str;

  if (str == "custom sticker") {
    const userInput = window.prompt("Type something for your custom sticker:");
    if (userInput && userInput != "") {
      currentSticker = userInput;
      stickers.push(userInput);
      createStickerButtons(userInput);
      // eslint-disable-next-line @typescript-eslint/no-magic-numbers
      const latestSticker = stickerButton[stickerButton.length - 1];
      listenCustomSticker(latestSticker);
    }
  }
}

function redraw() {
  // eslint-disable-next-line @typescript-eslint/no-magic-numbers
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  commands.forEach((cmd) => cmd.execute(ctx));

  if (cursorCommand) {
    cursorCommand.execute();
  }
}

function createButtons(buttons: Buttons[]) {
  for (const butt of buttons) {
    butt.button.textContent = butt.buttonText;
    app.append(butt.button);
  }
  const header = document.createElement("h1");
  header.innerHTML = "Harry's Game";

  const appTitle: HTMLElement = document.createElement("h1");
  appTitle.innerHTML = "Welcome To Art Class";

  app.append(header);
  app.append(appTitle);
}

function createStickerButtons(str: string) {
  const temp: HTMLButtonElement = document.createElement("button");
  temp.innerHTML = str;
  stickerButton.push(temp);
  app.append(temp);
}

function listenCustomSticker(stickerbutton: HTMLButtonElement) {
  stickerbutton.addEventListener("click", () => {
    eventListenerSticker(stickerbutton.innerHTML);
  });
}

function exportListener() {
  const canvasExport: HTMLCanvasElement = document.createElement("canvas");
  canvasExport.height = 1024;
  canvasExport.width = 1024;
  const scaleFactor = canvasExport.width / canvas.width;
  const ctxExport = canvasExport.getContext("2d")!;
  ctxExport.scale(scaleFactor, scaleFactor);
  commands.forEach((cmd) => cmd.execute(ctxExport));
  const anchor = document.createElement("a");
  anchor.href = canvasExport.toDataURL("image/png");
  anchor.download = "sketchpad.png";
  anchor.click();
}

function getRandomInt(max: number) {
  return Math.floor(Math.random() * max);
}
