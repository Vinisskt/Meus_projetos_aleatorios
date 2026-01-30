local state = {
  win = nil,
  buf = nil,
}

-- fechar janela
local close_win_buf = function()
  vim.api.nvim_win_close(state.win, true)
  state.win = nil
end

-- criar janela flutuante
local function create_window_float(opts)
  opts = opts or {}

  local width = opts.width or math.floor(vim.o.columns * 0.8)
  local height = opts.height or math.floor(vim.o.lines * 0.8)

  local col = math.floor((vim.o.columns - width) / 2)
  local row = math.floor((vim.o.lines - height) / 2)

  if state.buf == nil then
    state.buf = vim.api.nvim_create_buf(false, true)
  end

  local win_config = {
    relative = "editor",
    width = width,
    height = height,
    col = col,
    row = row,
    border = "double",
    style = "minimal",
  }

  if state.win == nil then
    state.win = vim.api.nvim_open_win(state.buf, true, win_config)
  end

  vim.keymap.set("n", "<leader>tq", close_win_buf, { desc = "[T]ranslate [Q]uit" })

  vim.api.nvim_create_autocmd("BufWinLeave", {
    buffer = state.buf,
    callback = function()
      state.win = nil
      state.buf = nil
    end,
  })

  if state.buf ~= nil then
    vim.api.nvim_buf_set_lines(state.buf, 0, -1, false, opts)
  end
end

-- traduçao usando shell translator
local function translate_text()
  local cursor = vim.fn.line(".")
  local text_buffer = vim.api.nvim_buf_get_lines(0, cursor, cursor + 30, false)
  local text_join = vim.fn.join(text_buffer, "\n")
  local text_string = vim.fn.shellescape(text_join)
  local text_translate = vim.fn.system("trans -b :pt " .. text_string)
  return text_translate
end

local function translate_line()
  local cursor = vim.fn.line(".")
  local text_buffer = vim.api.nvim_buf_get_lines(0, cursor, cursor + 1, false)
  local text_join = vim.fn.join(text_buffer, "\n")
  local text_string = vim.fn.shellescape(text_join)
  local text_translate = vim.fn.system("trans -b :pt " .. text_string)
  return text_translate
end

-- principal
local mainLines = function()
  local text_translate = translate_text()
  local text = vim.split(text_translate, "\n")
  create_window_float(text)
end

local mainLine = function()
  local text_translate = translate_line()
  local text = vim.split(text_translate, "\n")
  create_window_float(text)
end

vim.keymap.set("n", "<leader>tb", mainLines, { desc = "[T]ranslator [B]uffer" })
vim.keymap.set("n", "<leader>tl", mainLine, { desc = "[T]ranslator [L]ine" })

return {}
