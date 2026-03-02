import { useState } from 'react'
import { Outlet } from 'react-router-dom'
import Sidebar from './Sidebar'
import type { Theme } from '../types'

function buildTheme(dark: boolean): Theme {
  return {
    bg:            dark ? '#1e1e1e' : '#ffffff',
    text:          dark ? '#ffffff' : '#111111',
    border:        dark ? '#555'    : '#ddd',
    axis:          dark ? '#888'    : '#333',
    tick:          dark ? '#888'    : '#333',
    tickText:      dark ? '#aaa'    : '#555',
    sidebar:       dark ? '#252526' : '#f5f5f5',
    sidebarActive: dark ? '#4fc3f7' : '#1976d2',
  }
}

export default function Layout() {
  const [dark, setDark] = useState(true)
  const theme = buildTheme(dark)

  return (
    <div style={{ display: 'flex', minHeight: '100vh', background: theme.bg, color: theme.text }}>
      <Sidebar theme={theme} />

      <div style={{ flex: 1, display: 'flex', flexDirection: 'column' }}>
        <header style={{
          display: 'flex',
          alignItems: 'center',
          justifyContent: 'space-between',
          padding: '12px 24px',
          borderBottom: `1px solid ${theme.border}`,
        }}>
          <span style={{ fontWeight: 700, fontSize: 18 }}>Computational Geometry</span>
          <button onClick={() => setDark(d => !d)}>
            {dark ? '☀ Light' : '☾ Dark'}
          </button>
        </header>

        <main style={{ flex: 1, padding: '24px' }}>
          <Outlet context={{ theme }} />
        </main>
      </div>
    </div>
  )
}
