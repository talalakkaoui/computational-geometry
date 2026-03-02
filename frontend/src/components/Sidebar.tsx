import { NavLink } from 'react-router-dom'
import type { Theme } from '../types'

type Algorithm = { label: string; path: string }

const algorithms: Algorithm[] = [
  { label: 'Point Distance',          path: '/algorithms/distance' },
  { label: 'Convex Hull',             path: '/algorithms/convex-hull' },
  { label: 'Line Segment Intersection', path: '/algorithms/segment-intersection' },
]

type SidebarProps = { theme: Theme }

export default function Sidebar({ theme }: SidebarProps) {
  return (
    <nav style={{
      width: '220px',
      minHeight: '100vh',
      background: theme.sidebar,
      borderRight: `1px solid ${theme.border}`,
      padding: '24px 0',
      flexShrink: 0,
    }}>
      <p style={{ padding: '0 16px 12px', fontSize: 11, fontWeight: 600, letterSpacing: '0.08em', color: theme.tickText, textTransform: 'uppercase' }}>
        Algorithms
      </p>
      {algorithms.map(({ label, path }) => (
        <NavLink
          key={path}
          to={path}
          style={({ isActive }) => ({
            display: 'block',
            padding: '8px 16px',
            fontSize: 14,
            textDecoration: 'none',
            color: isActive ? theme.sidebarActive : theme.text,
            background: isActive ? theme.bg : 'transparent',
            borderLeft: isActive ? `3px solid ${theme.sidebarActive}` : '3px solid transparent',
          })}
        >
          {label}
        </NavLink>
      ))}
    </nav>
  )
}
