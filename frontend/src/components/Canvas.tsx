import { useState, useEffect } from 'react'
import type { Polygon2D, Point2D, Theme } from '../types'

type PointEntry = { point: Point2D; label: string; color: string }

type CanvasProps = {
  points: PointEntry[]
  onPointClick: (p: Point2D) => void
  theme: Theme
  polygon?: Polygon2D
}

export default function Canvas({ points, onPointClick, theme, polygon }: CanvasProps) {
  const [width, setWidth] = useState(window.innerWidth * 0.8)
  const [height, setHeight] = useState(window.innerHeight * 0.8)

  const centerX = width / 2
  const centerY = height / 2
  const divisions = 10
  const stepX = width / divisions
  const stepY = height / divisions

  useEffect(() => {
    function handleResize() {
      setWidth(window.innerWidth * 0.8)
      setHeight(window.innerHeight * 0.8)
    }
    window.addEventListener('resize', handleResize)
    return () => window.removeEventListener('resize', handleResize)
  }, [])

  const xTicks = Array.from({ length: divisions - 1 }, (_, i) => ({
    svgX: stepX * (i + 1),
    label: i + 1 - divisions / 2,
  }))

  const yTicks = Array.from({ length: divisions - 1 }, (_, i) => ({
    svgY: stepY * (i + 1),
    label: divisions / 2 - (i + 1),
  }))

  function handleClick(e: React.MouseEvent<SVGSVGElement>) {
    const rect = e.currentTarget.getBoundingClientRect()
    const svgX = e.clientX - rect.left
    const svgY = e.clientY - rect.top
    onPointClick({
      x: (svgX - centerX) / stepX,
      y: -(svgY - centerY) / stepY,
    })
  }

  return (
    <svg
      width={width}
      height={height}
      style={{ border: `1px solid ${theme.border}`, background: theme.bg, display: 'block' }}
      onClick={handleClick}
    >
      {/* Axes */}
      <line x1={0} y1={centerY} x2={width} y2={centerY} stroke={theme.axis} />
      <line x1={centerX} y1={0} x2={centerX} y2={height} stroke={theme.axis} />

      {/* X-axis ticks and labels */}
      {xTicks.map(({ svgX, label }) => (
        <g key={`x-${label}`}>
          <line x1={svgX} y1={centerY - 5} x2={svgX} y2={centerY + 5} stroke={theme.tick} />
          {label !== 0 && (
            <text x={svgX} y={centerY + 18} textAnchor="middle" fontSize={11} fill={theme.tickText}>{label}</text>
          )}
        </g>
      ))}

      {/* Y-axis ticks and labels */}
      {yTicks.map(({ svgY, label }) => (
        <g key={`y-${label}`}>
          <line x1={centerX - 5} y1={svgY} x2={centerX + 5} y2={svgY} stroke={theme.tick} />
          {label !== 0 && (
            <text x={centerX - 8} y={svgY + 4} textAnchor="end" fontSize={11} fill={theme.tickText}>{label}</text>
          )}
        </g>
      ))}

      {/* Polygon */}
      {polygon && (() => {
        const svgPoints = polygon.vertices.map((p: Point2D) => `${p.x * stepX + centerX},${-p.y * stepY + centerY}`).join(' ')
        return polygon.isClosed
          ? <polygon points={svgPoints} fill="rgba(79, 195, 247, 0.15)" stroke="#4fc3f7" strokeWidth={2} />
          : <polyline points={svgPoints} fill="none" stroke="#4fc3f7" strokeWidth={2} />
      })()}

      {/* Points */}
      {points.map(({ point, label, color }) => (
        <g key={label}>
          <circle
            cx={point.x * stepX + centerX}
            cy={-point.y * stepY + centerY}
            r={5}
            fill={color}
          />
          <text
            x={point.x * stepX + centerX + 8}
            y={-point.y * stepY + centerY}
            fontSize={12}
            fill={theme.text}
          >
            {label}
          </text>
        </g>
      ))}
    </svg>
  )
}
